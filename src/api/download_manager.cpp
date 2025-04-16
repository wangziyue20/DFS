#include "download_manager.h"
#include "calculateSHA.h"
#include "file_manager.h"
#include "local_node_info.h"
#include "mysql_client.h"
#include "redis_client.h"

namespace dfs {
crow::response DownloadManager::downloadById(const std::string id) {
  try {
    NodeInfo node = dfs::LocalNodeInfo::get();

    dfs::RedisClient redis;
    dfs::MySQLClient::FileMeta meta = redis.getMetaData(id);
    std::string filename = meta.filename;

    // redis中没有，从MySQL查询
    if (!filename.empty()) {
      std::cout << "[Redis] Cache hit " << id << "->" << filename << ">>>"
                << std::endl;
    } else {
      std::cout << "[Redis] Cache miss " << id << ">>>" << std::endl;
      dfs::MySQLClient mysql;
      meta = mysql.getMetaData(id);
      if (meta.filename.empty()) {
        return crow::response(404, "Not found>>>");
      }

      // path = node.storage_path;
      filename = meta.filename;
      std::cout << "path :" << filename << ">>>" << std::endl;

      redis.cacheMeta(meta, 3600);
      std::cout << "[Redis] Cache writes " << id << "->" << filename << ">>>"
                << std::endl;
    }

    //获取路径
    std::string path = node.storage_path + "/" + meta.uuid;

    //读取文件内容
    std::string file_content = dfs::FileManager::readFile(path);
    if (file_content.empty()) {
      CROW_LOG_ERROR << "Empty content at path >>>" << path;
      return crow::response(404, "Not found content>>>");
    }
    //读取校验和
    std::string download_md5 = calculateSHA256(path);

    if (download_md5 != meta.checksum) {
      return crow::response(500, "File integrity check falied");
    }

    //准备文件下载响应
    crow::response res(file_content);
    res.add_header("Content-Type", "application/octet-stream");
    res.add_header("Content-Disposition",
                   "attachment; filename=\"" + filename + "\"");
    res.add_header("Content-Length", std::to_string(file_content.size()));
    return res;
  } catch (const std::exception &e) {
    return crow::response(500,
                          std::string("Download server failed>>>") + e.what());
  } catch (...) {
    return crow::response(500, "Download server failed: unknown>>>");
  }
}
} // namespace dfs