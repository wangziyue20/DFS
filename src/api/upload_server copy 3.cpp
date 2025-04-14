#include <curl/curl.h>
#include <iostream>
// #include <nlohmann/json.hpp>

#include "crow.h"
#include "node_register.h"
#include "node_selector.h"
#include "upload_manager.h"

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  //将收到的数据追加到字符串中
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

int main() {
  crow::SimpleApp app;

  dfs::initNodes();
  // 文件上传端点
  CROW_ROUTE(app, "/upload")
      .methods("POST"_method)([](const crow::request &req) {
        try {
          dfs::NodeSelector selector("http://127.0.0.1:8080/get_nodes");
          dfs::NodeInfo node = selector.select();

          std::string url =
              "http://" + node.ip + ":" + std::to_string(node.port) + "/upload";
          std::string filename = req.get_header_value("Filename");
          if (filename.empty()) {
            return crow::response(400, "Missing Filename header >>>");
          }

          CURL *curl = curl_easy_init();
          std::string response_string;

          struct curl_slist *header = NULL;
          header = curl_slist_append(header, ("Filename: " + filename).c_str());

          curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
          curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
          curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req.body.c_str());
          curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, req.body.size());
          curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
          curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

          CURLcode res = curl_easy_perform(curl);
          curl_slist_free_all(header);
          curl_easy_cleanup(curl);

          if (res != CURLE_OK) {
            std::cerr << "Failed to forward upload" << curl_easy_strerror(res)
                      << "\n";
            return crow::response(500, "Failed to forward upload >>>");
          }

          return crow::response(200, response_string);
        } catch (const std::exception &e) {
          return crow::response(500, std::string("Upload Failed: ") + e.what());
        } catch (...) {
          return crow::response(500, std::string("Upload Failed: Unknown "));
        }
      });

  // 启动服务器
  app.port(18080).multithreaded().run();
  return 0;
}