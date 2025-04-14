#pragma once

#include "data_node.h"
#include <vector>

namespace dfs {
class NodeSelector {
private:
  std::vector<DataNode> nodes;
  size_t current_index = 0;
public:
  void registerNode(const DataNode &node);
  DataNode selectNode();
};
} // namespace dfs