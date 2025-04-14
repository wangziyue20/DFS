// #include <curl/curl.h>
#include <iostream>
// #include <nlohmann/json.hpp>

#include "crow.h"
#include "httplib.h"
#include "node_selector.h"
// #include "upload_manager.h"
// #include "node_register.h"

int main() {
  crow::SimpleApp app;

  // 文件上传端点
  CROW_ROUTE(app, "/upload")
      .methods("POST"_method)([](const crow::request &req) {
        auto filename = req.get_header_value("filename");
        if (filename.empty()) {
          return crow::response(400, "Missing Filename header >>>\n");
        }

        dfs::NodeSelector selector("http://127.0.0.1:8080/get_nodes");
        dfs::NodeInfo node = selector.select();

        httplib::Client client(node.ip, node.port);
        httplib::Headers headers = {{"filename", filename}};
        auto res = client.Post("/internal_upload", headers, req.body,
                               "application/octet-stream");

        if (res && res->status == 200) {
          return crow::response(200, res->body);
        } else {
          return crow::response(500, "Forward upload failed >>>");
        }
      });

  // 启动服务器
  app.port(8081).multithreaded().run();
  return 0;
}