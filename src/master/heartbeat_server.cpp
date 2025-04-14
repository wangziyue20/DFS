#include "heartbeat_server.h"

#include <crow/json.h>

namespace dfs {
HeartbeatServer::HeartbeatServer(muduo::net::EventLoop *loop, int addr,
                                 NodeManager *manager)
    : server_(loop, muduo::net::InetAddress(addr), "HeartbeatServer"),
      manager_(manager) {
  server_.setConnectionCallback(
      std::bind(&HeartbeatServer::onConnect, this, std::placeholders::_1));
  server_.setMessageCallback(
      std::bind(&HeartbeatServer::onMessage, this, std::placeholders::_1,
                std::placeholders::_2, std::placeholders::_3));
}

void HeartbeatServer::start() { server_.start(); }

void HeartbeatServer::onConnect(const muduo::net::TcpConnectionPtr &conn) {
  LOG_INFO << "Heartbeat Connection from " << conn->peerAddress().toIpPort();
}

void HeartbeatServer::onMessage(const muduo::net::TcpConnectionPtr &conn,
                                muduo::net::Buffer *buffer,
                                muduo::Timestamp time) {
  std::string msg = buffer->retrieveAllAsString();
  if (msg.empty()) {
    LOG_WARN << "Empty heartbeat from " << conn->peerAddress().toIpPort();
    return;
  }

  try {
    auto json = crow::json::load(msg);
    if (!json) {
      LOG_ERROR << "Invalid heartbeat JSON >>>";
      return;
    }

    DataNode node;
    node.id = json["id"].i();
    node.ip = json["ip"].s();
    node.port = json["port"].i();
    node.storage_path = json["storage_path"].s();
    node.available_space = json["available_space"].i();
    node.last_heartbeat = std::time(nullptr);
    node.online = true;

    manager_->registerOrUpdate(node);

    LOG_INFO << "Received heartbeat from :" << node.id;
  } catch (...) {
    LOG_ERROR << "Failed to parse heartbeat msg >>>";
  }
}
} // namespace dfs