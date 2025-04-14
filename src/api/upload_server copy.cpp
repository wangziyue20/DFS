#include "file_manager.h"
#include "mysql_client.h"
#include "redis_client.h"

#include <crow.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dfs {
UploadServer::UploadServer(int port)
    : server_(&loop_, muduo::net::InetAddress(port), "UploadServer") {
  server_.setHttpCallback(std::bind(&UploadServer::onRequest, this,
                                    std::placeholders::_1,
                                    std::placeholders::_2));
}
void UploadServer::start() {
  server_.setThreadNum(4); // 设置多线程可选
  server_.start();
  loop_.loop();
}

void UploadServer::onRequest(const muduo::net::HttpRequest &req,
                             muduo::net::HttpResponse *resp) {
  if (req.method() == muduo::net::HttpRequest::Method::kPost &&
      req.path() == "/upload") {
    std::string body = req.getHeader("Content-Length") != "" ? req.query() : "";
    std::string body = req.body(); // 直接获取请求体

    if (body.empty()) {
      resp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
      resp->setContentType("text/plain");
      resp->setBody("Empty body>>>");
      return;
    }

    try {
      json js = json::parse(body);
      std::string filename = js["filename"];
      std::string data = js["data"];

      std::string path = dfs::FileManager::saveFile(filename, data);
      size_t size = dfs::FileManager::getFileSize(data);

      dfs::MySQLClient::FileMeta file = {filename, path, size};
      dfs::MySQLClient mysql;
      mysql.insertMetaData(file);

      dfs::RedisClient redis;
      redis.cacheMeta(filename, path);

      resp->setStatusCode(muduo::net::HttpResponse::k200Ok);
      resp->setContentType("text/plain");
      resp->setBody("Upload receive>>>");
    } catch (...) {
      resp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
      resp->setContentType("text/plain");
      resp->setBody("Upload receive>>>");
    }
  } else {
    resp->setStatusCode(muduo::net::HttpResponse::k404NotFound);
    resp->setContentType("text/plain");
    resp->setBody("Upload receive>>>");
  }
}
} // namespace dfs