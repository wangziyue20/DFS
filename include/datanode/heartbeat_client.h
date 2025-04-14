#pragma once

#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpClient.h>
#include <thread>

namespace dfs {
class HeartbeatClient {
public:
  HeartbeatClient(muduo::net::EventLoop *loop, const std::string &master_ip,
                  int master_port, int id, const std::string &ip, int port,
                  const std::string &storage_path);
  void start();
  void stop();

private:
  muduo::net::EventLoop *loop_;
  muduo::net::TcpConnectionPtr conn_;
  std::unique_ptr<muduo::net::TcpClient> client_;

  std::atomic<bool> running_;
  std::thread heartbeat_thread_;

  std::string master_ip_;
  int master_port_;
  int id_;
  std::string ip_;
  int port_;
  std::string storage_path_;
};
} // namespace dfs