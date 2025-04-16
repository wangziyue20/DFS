#include <iostream>
#include <uuid/uuid.h>

#include "calculateSHA.h"
#include "crow.h"
#include "httplib.h"
#include "mysql_client.h"
#include "node_selector.h"

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
        // std::vector<dfs::NodeInfo> nodes = selector.selectN(3);
        std::vector<dfs::NodeInfo> nodes = selector.selectAll();

        dfs::MySQLClient::FileMeta meta;
        dfs::MySQLClient mysqlClient;

        //使用同一个uuid
        uuid_t uuid;
        char uuid_filename[37];
        uuid_generate(uuid);
        uuid_unparse_lower(uuid, uuid_filename);

        meta.filename = filename;
        meta.uuid = uuid_filename;
        meta.size = req.body.size();

        std::string file_data = req.body;

        // 上传时临时保存文件到磁盘，再用路径来计算 SHA256
        std::string temp_path = "/tmp/" + std::string(uuid_filename);
        std::ofstream temp_file(temp_path, std::ios::binary);
        if (!temp_file) {
          return crow::response(500, "Failed to write temp file >>>");
        }
        temp_file.write(req.body.c_str(), req.body.size());
        temp_file.close();

        std::string md5_checksum = dfs::calculateSHA256(temp_path);
        meta.checksum = md5_checksum;

        int success_count = 0;
        int replica_required = 2;

        for (const auto &node : nodes) {
          httplib::Client client(node.ip, node.port);
          httplib::Headers headers = {{"filename", filename},
                                      {"uuid", uuid_filename}};

          auto res = client.Post("/internal_upload", headers, req.body,
                                 "application/octet-stream");

          if (res && res->status == 200) {
            dfs::MySQLClient::Replica r;
            r.node_ip = node.ip;
            r.node_port = node.port;

            r.filepath = node.storage_path;
            meta.replicas.push_back(r);
            success_count++;
          }
          if (success_count >= replica_required) {
            break;
          }
        }

        if (success_count >= replica_required) {
          mysqlClient.insertMetaData(meta);
          return crow::response(200, "Upload seccess >>>");

        } else {
          return crow::response(500, "Forward upload failed >>>");
        }
      });

  // 启动服务器
  app.port(8081).multithreaded().run();
  return 0;
}