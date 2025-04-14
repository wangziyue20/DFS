#pragma once

#include "data_node.h"
#include <mutex>
#include <unordered_map>
#include <vector>

namespace dfs {
class NodeManager {
public:
  void registerNode(const DataNode &node);
  void updateHeartbeat(int node_id);
  std::vector<DataNode> getOnlineNodes();
  void registerOrUpdate(const DataNode &node);

private:
  std::mutex mutex_;
  std::unordered_map<int, DataNode> nodes_;
};
} // namespace dfs