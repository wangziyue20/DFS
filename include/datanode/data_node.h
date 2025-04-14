#pragma once

#include <string>

struct DataNode {
  int id;
  std::string ip;
  int port;
  std::string storage_path;
  size_t available_space;
  time_t last_heartbeat;
  bool online;
};