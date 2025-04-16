#pragma once

#include <mysql/mysql.h>
#include <string>
#include <vector>

namespace dfs {
class MySQLClient {
private:
  MYSQL *connection_;

public:
  MySQLClient();
  ~MySQLClient();

  struct Replica {
    std::string filepath;
    std::string node_ip;
    int node_port;
  };

  struct FileMeta {
    std::string uuid;
    std::string filename;
    size_t size;
    std::string checksum;
    std::vector<Replica> replicas;
  };

  void insertMetaData(const FileMeta &file);
  FileMeta getMetaData(const std::string &id);
  bool deleteMetaData(const std::string &id);
};
} // namespace dfs