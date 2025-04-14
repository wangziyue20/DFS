#include "global_node_manager.h"

namespace dfs {
NodeManager &getGlobalNodeManager() {
  static NodeManager manager;
  return manager;
}
} // namespace dfs