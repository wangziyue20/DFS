#pragma once

#include "node_selector.h"

namespace dfs {
class LocalNodeInfo {
public:
  static void init(const NodeInfo &info);
  static NodeInfo &get();

private:
  static NodeInfo local_info_;
};
} // namespace dfs