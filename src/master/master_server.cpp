#include "crow.h"
#include "global_node_manager.h"
#include "heartbeat_server.h"
#include <nlohmann/json.hpp>

#include <iostream>
#include <muduo/net/EventLoop.h>

using json = nlohmann::json;

int main() {
  muduo::net::EventLoop loop;

  dfs::HeartbeatServer server(&loop, 9000, &dfs::getGlobalNodeManager());
  std::cout << "Global NodeManager address: " << &dfs::getGlobalNodeManager()
            << std::endl;

  server.start();

  crow::SimpleApp app;
  CROW_ROUTE(app, "/get_nodes")
  ([] {
    auto nodes = dfs::getGlobalNodeManager().getOnlineNodes();
    json res;
    for (auto node : nodes) {
      res.push_back({
          {"id", node.id},
          {"ip", node.ip},
          {"port", node.port},
          {"path", node.storage_path},
      });
    }
    return crow::response(res.dump());
  });

  std::thread node_thread([&]() { app.port(8080).multithreaded().run(); });

  loop.loop();
  node_thread.join();
  return 0;
}