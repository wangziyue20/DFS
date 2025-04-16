#include "crow.h"
#include "httplib.h"
#include "mysql_client.h"
#include "redis_client.h"

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/delete/<string>")
      .methods("POST"_method)([](const crow::request &req, std::string uuid) {
        dfs::MySQLClient mysql;
        dfs::RedisClient redis;
        auto meta = redis.getMetaData(uuid);
        if (meta.filename.empty()) {
          meta = mysql.getMetaData(uuid);
          if (meta.filename.empty()) {
            return crow::response(404, "File not found");
          }
        }

        //删除各个副本
        for (auto &replica : meta.replicas) {
          httplib::Client client(replica.node_ip, replica.node_port);
          auto res = client.Post(("/internal_delete/" + uuid).c_str());
          if (!res || res->status != 200) {
            std::cerr << "Delete from node failed : " << replica.node_ip
                      << "port: " << replica.node_port << "\n";
          }
        }

        bool result = true;
        result |= mysql.deleteMetaData(uuid);
        result |= redis.removeCache(uuid);

        if (result) {
          return crow::response(200, "Deleted all nodes sucessfully >>> ");
        }
        return crow::response(500, "Deleted all nodes failed >>>");
      });

  app.port(8083).multithreaded().run();
}