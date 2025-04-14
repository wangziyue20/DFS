#include "local_node_info.h"

namespace dfs {
NodeInfo LocalNodeInfo::local_info_;
void LocalNodeInfo::init(const NodeInfo &info) { local_info_ = info; }
NodeInfo &LocalNodeInfo::get() { return local_info_; }
} // namespace dfs