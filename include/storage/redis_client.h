#pragma once

#include <hiredis/hiredis.h>
#include <mysql_client.h>
#include <string>
namespace dfs {
class RedisClient {
public:
  RedisClient();
  ~RedisClient();

  void cacheMeta(const dfs::MySQLClient::FileMeta &meta, int ttl_seconds);
  MySQLClient::FileMeta getMetaData(const std::string &key);

private:
  redisContext *context_;
};
} // namespace dfs