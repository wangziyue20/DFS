#include "nodeManager.h"

#include <ctime>
#include <iostream>

namespace dfs {
void NodeManager::registerNode(const DataNode &node) {
  std::lock_guard<std::mutex> lock(mutex_);
  nodes_[node.id] = node;
}

void NodeManager::updateHeartbeat(int node_id) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = nodes_.find(node_id);
  if (it != nodes_.end()) {
    it->second.last_heartbeat = std::time(nullptr);
    it->second.online = true;
  } else {
    throw std::runtime_error("cannot find node >>>");
  }
}

std::vector<DataNode> NodeManager::getOnlineNodes() {
  std::lock_guard<std::mutex> lock(mutex_);
  std::vector<DataNode> res;

  time_t now = std::time(nullptr);

  for (auto &[id, node] : nodes_) {
    if (now - node.last_heartbeat < 10) { // 10s内视为在线
      res.push_back(node);
    } else {
      node.online = false;
    }
  }

  return res;
}

void NodeManager::registerOrUpdate(const DataNode &node) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (nodes_.find(node.id) == nodes_.end()) {
    std::cout << "Register new node :" << node.id << std::endl;
    std::cout << "Register new node id: " << node.id << ", ip: " << node.ip
              << ", port: " << node.port << ", path: " << node.storage_path
              << std::endl;

    nodes_[node.id] = node;
  } else {
    nodes_[node.id].last_heartbeat = std::time(nullptr);
    nodes_[node.id].available_space = node.available_space;
    nodes_[node.id].online = true;
  }
}
} // namespace dfs