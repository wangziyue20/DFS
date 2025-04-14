#include "heartbeat_client.h"

#include <crow/json.h>

namespace dfs {
HeartbeatClient::HeartbeatClient(muduo::net::EventLoop *loop,
                                 const std::string &master_ip, int master_port,
                                 int id, const std::string &ip, int port,
                                 const std::string &storage_path)
    : loop_(loop), master_ip_(master_ip), master_port_(master_port), id_(id),
      ip_(ip), port_(port), storage_path_(storage_path), running_(true) {}

void HeartbeatClient::start() {
  muduo::net::InetAddress serverAddr(master_ip_, master_port_);

  //只创建一个client_
  client_ = std::make_unique<muduo::net::TcpClient>(loop_, serverAddr,
                                                    "HeartbeatClient");
  client_->setConnectionCallback(
      [this](const muduo::net::TcpConnectionPtr &conn) {
        if (conn->connected()) {
          conn_ = conn;
          LOG_INFO << "Connected to server >>>";
        } else {
          LOG_ERROR << "Heartbeat failed >>>";
          conn_.reset();
        }
      });

  client_->connect();

  running_ = true;
  heartbeat_thread_ = std::thread([&]() {
    while (running_) {
      if (conn_ && conn_->connected()) {
        crow::json::wvalue heartbaet;
        heartbaet["id"] = id_;
        heartbaet["ip"] = ip_;
        heartbaet["port"] = port_;
        heartbaet["storage_path"] = storage_path_;
        heartbaet["available_space"] = 1024 * 1024;

        std::string msg = heartbaet.dump();
        conn_->send(msg);
        LOG_INFO << "Send heartbeat";
      }
      std::this_thread::sleep_for(std::chrono::seconds(3));
    }
  });
}

void HeartbeatClient::stop() {
  running_ = false;
  if (heartbeat_thread_.joinable()) {
    heartbeat_thread_.join();
  }
}

} // namespace dfs