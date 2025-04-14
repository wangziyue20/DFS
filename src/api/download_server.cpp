#include "crow.h"
#include "httplib.h"
#include "mysql_client.h"
#include "redis_client.h"

#include <iostream>
#include <nlohmann/json.hpp>

int main() {
  crow::SimpleApp app;

  // 文件上传端点（保持不变）
  CROW_ROUTE(app, "/download/<string>")
  ([](const crow::request &req, std::string id) {
    dfs::RedisClient redis;
    dfs::MySQLClient::FileMeta meta = redis.getMetaData(id);
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
      redis.cacheMeta(meta, 3600);
      std::cout << "[Redis] Cache writes " << id << "->" << path << ">>>"
                << std::endl;
    }

    httplib::Client client(meta.node_ip, meta.node_port);
    auto res = client.Get(("/internal_download/" + meta.uuid).c_str());

    if (res && res->status == 200) {
      crow::response rsp(res->body);
      rsp.add_header("Content-Disposition",
                     "attachment; filename=\"" + meta.filename + "\"");
      rsp.add_header("Content-Type", "application/octet-stream");
      return rsp;
    } else {
      return crow::response(500, "Forward download failed");
    }
  });

  // 启动服务器
  app.port(8082).multithreaded().run();
  return 0;
}