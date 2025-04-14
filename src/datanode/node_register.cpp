#include "node_register.h"

namespace dfs {
// 1.注册节点
static NodeSelector global_selector;

NodeSelector &getGlobalNodeSelector() { return global_selector; }
void initNodes() {
  DataNode node1, node2;

  node1.id = 1;
  node1.storage_path = "/home/book/Desktop/chat/data/upload1";
  // node1.address = "127.0.0.1:8001";
  node1.available_space = 1024 * 1024;
  node1.online = true;
  global_selector.registerNode(node1);

  node2.id = 2;
  node2.storage_path = "/home/book/Desktop/chat/data/upload2";
  // node2.address = "127.0.0.1:8002";
  node2.available_space = 1024 * 1024;
  node2.online = true;
  global_selector.registerNode(node2);
}
} // namespace dfs