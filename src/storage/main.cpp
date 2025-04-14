#include "file_manager.h"
#include "mysql_client.h"
#include "redis_client.h"

#include <iostream>

int main() {
  std::string filename = "test.txt";
  std::string file_data = "hello distributed file system!";

  // 保存文件
  std::string path = dfs::FileManager::saveFile(filename, file_data);
  size_t size = dfs::FileManager::getFileSize(file_data);

  dfs::MySQLClient::FileMeta file = {filename, path, size};
  // 写入元数据到 MySQL
  dfs::MySQLClient mysql;
  mysql.insertMetaData(file);

  // 缓存元数据到 Redis
  dfs::RedisClient redis;
  redis.cacheMeta(filename, path);

  return 0;
}
