#include "heartbeat_server.h"

#include <muduo/net/EventLoop.h>

int main() {
  muduo::net::EventLoop loop;
  dfs::NodeManager manager;

  DataNode node1;
  node1.id = 1;
  node1.storage_path = "/home/book/Desktop/chat/data/upload1";
  node1.ip = "127.0.0.1";
  node1.port = 9001;
  node1.available_space = 1024 * 1024;
  node1.online = false;

  DataNode node2;
  node2.id = 2;
  node2.storage_path = "/home/book/Desktop/chat/data/upload2";
  node1.ip = "127.0.0.1";
  node2.port = 9002;
  node2.available_space = 1024 * 1024;
  node2.online = false;

  manager.registerNode(node2);
  dfs::HeartbeatServer server(&loop, 9000, &manager);

  server.start();
  loop.loop();

  return 0;
}