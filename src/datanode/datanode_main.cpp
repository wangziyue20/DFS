#include "crow.h"
#include "download_manager.h"
#include "heartbeat_client.h"
#include "local_node_info.h"
#include "upload_manager.h"

#include <fstream>
#include <muduo/net/EventLoop.h>
#include <thread>

struct Config {
  int id;
  std::string ip;
  int port;
  std::string storage_path;
  std::string master_ip;
  int master_port;
};

Config parseConfig(const std::string &filename) {
  Config cfg;
  std::ifstream in(filename);
  std::string line;

  while (std::getline(in, line)) {
    std::istringstream iss(line);
    std::string key, value;
    if (std::getline(iss, key, '=') && std::getline(iss, value)) {
      if (key == "id")
        cfg.id = std::stoi(value);
      if (key == "ip")
        cfg.ip = value;
      if (key == "port")
        cfg.port = std::stoi(value);
      if (key == "storage_path")
        cfg.storage_path = value;
      if (key == "master_ip")
        cfg.master_ip = value;
      if (key == "master_port")
        cfg.master_port = std::stoi(value);
    }
  }
  return cfg;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: ./datanode_main <config>" << std::endl;
  }

  Config cfg = parseConfig(argv[1]);

  //初始化节点信息
  dfs::NodeInfo self_node(cfg.id, cfg.ip, cfg.port, cfg.storage_path);
  dfs::LocalNodeInfo::init(self_node);
  muduo::net::EventLoop loop;

  dfs::HeartbeatClient heartbeat_client(&loop, cfg.master_ip, cfg.master_port,
                                        cfg.id, cfg.ip, cfg.port,
                                        cfg.storage_path);
  heartbeat_client.start();

  std::thread upload_thread([&]() {
    crow::SimpleApp app;

    // 文件上传端点
    CROW_ROUTE(app, "/internal_upload")
        .methods("POST"_method)([](const crow::request &req) {
          return dfs::UploadManager::uploaderHandler(req);
        });

    //文件下载
    CROW_ROUTE(app, "/internal_download/<string>")
    ([](const crow::request &req, std::string id) {
      return dfs::DownloadManager::downloadById(id);
    });

    // 启动服务器
    app.port(cfg.port).multithreaded().run();
  });

  std::cout << "heartbeat & upload & download is running >>>" << std::endl;

  loop.loop();
  upload_thread.join();

  return 0;
}