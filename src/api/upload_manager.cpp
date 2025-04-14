#include "upload_manager.h"
#include "file_manager.h"
#include "local_node_info.h"
#include "mysql_client.h"
#include "node_selector.h"
#include "redis_client.h"

// #include "node_register.h"

#include <uuid/uuid.h>

namespace dfs {
crow::response UploadManager::uploaderHandler(const crow::request &req) {
  if (req.body.empty()) {
    return crow::response(400, "No file body received>>>");
  }

  auto filename_header = req.get_header_value("Filename");
  if (filename_header.empty()) {
    return crow::response(400, "No file header received");
  }

  try {
    uuid_t uuid;
    char uuid_filename[37];

    uuid_generate(uuid);
    uuid_unparse_lower(uuid, uuid_filename);

    NodeInfo node = dfs::LocalNodeInfo::get();
    if (node.storage_path.empty()) {
      throw std::runtime_error("Failed to select node");
    }
    std::cout << "Select node :" << node.id << std::endl;

    std::string oringinal_filename = filename_header;
    std::string stored_path = node.storage_path;
    std::string stored_name = uuid_filename + oringinal_filename;
    std::string file_data = req.body;
    std::string node_ip = node.ip;
    int node_port = node.port;

    std::cout << "stored_path : " << stored_path << std::endl;

    std::string path;
    //使用UUID保存文件
    path = dfs::FileManager::saveFile(stored_path, stored_name, file_data);
    if (path.empty()) {
      throw std::runtime_error("save file failed >>>");
    }
    size_t size = dfs::FileManager::getFileSize(file_data);

    //改上传流程为只写 MySQL
    dfs::MySQLClient::FileMeta file = {
        uuid_filename, oringinal_filename, path, size, node_ip, node_port};
    dfs::MySQLClient mysql;
    mysql.insertMetaData(file);

    // dfs::RedisClient redis;
    // redis.cacheMeta(uuid_filename, path, 60);

    // 构建成功响应
    crow::json::wvalue response;
    response["status"] = "success";
    response["original_filename"] = oringinal_filename;
    response["uuid"] = uuid_filename;
    response["size"] = size;
    return crow::response(200, response);
  } catch (const std::exception &e) {
    return crow::response(500,
                          std::string("Upload server failed>>>") + e.what());
  } catch (...) {
    return crow::response(500, "Upload server failed: unknown>>>");
  }
}
} // namespace dfs