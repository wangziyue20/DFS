#pragma once

#include <string>
#include <vector>

namespace dfs {
struct NodeInfo {
  int id;
  std::string ip;
  int port;
  std::string storage_path;

  NodeInfo() : id(0), ip(""), port(0), storage_path("") {}
  NodeInfo(int id, const std::string &ip, int port,
           const std::string &storage_path)
      : id(id), ip(ip), port(port), storage_path(storage_path) {}
};

class NodeSelector {
public:
  explicit NodeSelector(const std::string &master_utl);
  NodeInfo select();
  std::vector<NodeInfo> selectN(int count);
  std::vector<NodeInfo> selectAll();

private:
  std::vector<NodeInfo> fetchNodes();
  std::string master_utl_;
};
} // namespace dfs