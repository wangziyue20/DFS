#include "node_selector.h"

#include <stdexcept>

namespace dfs {
void NodeSelector::registerNode(const DataNode &node) { nodes.push_back(node); }
DataNode NodeSelector::selectNode() {
  if (nodes.empty()) {
    throw std::runtime_error("No nodes >>>");
  }

  size_t n = nodes.size();
  size_t check_node = 0;

  while (check_node < n) {
    DataNode node = nodes[current_index];
    current_index = (current_index + 1) % n;

    if (node.online) {
      return node;
    }

    check_node++;
  }

  throw std::runtime_error("No node online >>>");
}
} // namespace dfs