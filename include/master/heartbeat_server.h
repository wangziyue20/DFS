#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpServer.h>
#include <thread>

#include "nodeManager.h"

namespace dfs {
class HeartbeatServer {
public:
  HeartbeatServer(muduo::net::EventLoop *loop, int addr, NodeManager *manager);
  void start();

private:
  void onConnect(const muduo::net::TcpConnectionPtr &conn);
  void onMessage(const muduo::net::TcpConnectionPtr &conn,
                 muduo::net::Buffer *buffer, muduo::Timestamp time);

  muduo::net::TcpServer server_;
  NodeManager* manager_;
};
} // namespace dfs