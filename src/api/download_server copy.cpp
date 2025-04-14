#include "file_manager.h"
#include "mysql_client.h"
#include "redis_client.h"

#include "crow.h"
#include "crow/multipart.h"
#include <iostream>
#include <nlohmann/json.hpp>

#include "download_manager.h"

int main() {
  crow::SimpleApp app;

  // 文件上传端点（保持不变）
  CROW_ROUTE(app, "/download/<string>")
  ([](const crow::request &req, std::string id) {
    return dfs::DownloadManager::downloadById(id);
  });

  // 启动服务器
  app.port(8081).multithreaded().run();
  return 0;
}