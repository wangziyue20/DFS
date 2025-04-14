#pragma once

#include <mysql/mysql.h>
#include <string>

namespace dfs {
class MySQLClient {
private:
  MYSQL *connection_;

public:
  MySQLClient();
  ~MySQLClient();
  struct FileMeta {
    std::string uuid;
    std::string filename;
    std::string filepath;
    size_t size;
    std::string node_ip;
    int node_port;
  };
  void insertMetaData(const FileMeta &file);
  FileMeta getMetaData(const std::string &filename);
};
} // namespace dfs