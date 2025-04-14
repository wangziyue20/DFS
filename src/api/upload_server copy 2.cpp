#include "crow.h"
#include "crow/multipart.h"
#include <iostream>
#include <nlohmann/json.hpp>

#include "node_register.h"
#include "upload_manager.h"

int main() {
  crow::SimpleApp app;

  dfs::initNodes();
  // 文件上传端点
  CROW_ROUTE(app, "/upload")
      .methods("POST"_method)([](const crow::request &req) {
        return dfs::UploadManager::uploaderHandler(req);
      });

  // 启动服务器
  app.port(8080).multithreaded().run();
  return 0;
}