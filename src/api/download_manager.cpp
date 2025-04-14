#include "download_manager.h"
#include "file_manager.h"
#include "mysql_client.h"
#include "redis_client.h"

namespace dfs {
crow::response DownloadManager::downloadById(const std::string id) {
  try {
    dfs::RedisClient redis;
    dfs::MySQLClient::FileMeta meta = redis.getMetaData(id);
    std::string filename = meta.filename;
    std::string path = meta.filepath;

    // redis中没有，从MySQL查询
    if (!path.empty()) {
      std::cout << "[Redis] Cache hit " << id << "->" << path << ">>>"
                << std::endl;
    } else {
      std::cout << "[Redis] Cache miss " << id << ">>>" << std::endl;
      dfs::MySQLClient mysql;
      meta = mysql.getMetaData(id);
      if (meta.filename.empty()) {
        return crow::response(404, "Not found>>>");
      }

      path = meta.filepath;
      filename = meta.filename;
      std::cout << "path :" << path << ">>>" << std::endl;

      redis.cacheMeta(meta, 3600);
      std::cout << "[Redis] Cache writes " << id << "->" << path << ">>>"
                << std::endl;
    }

    //读取文件内容
    std::string file_content = dfs::FileManager::readFile(path);
    if (file_content.empty()) {
      CROW_LOG_ERROR << "Empty content at path >>>" << path;
      return crow::response(404, "Not found content>>>");
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