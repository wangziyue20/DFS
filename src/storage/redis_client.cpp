#include "redis_client.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace dfs {
RedisClient::RedisClient() {
  context_ = redisConnect("127.0.0.1", 6379);
  if (context_ == nullptr) {
    throw std::runtime_error("redisConnect failed");
  }
}
RedisClient::~RedisClient() {
  if (context_) {
    redisFree(context_);
  }
}

void RedisClient::cacheMeta(const dfs::MySQLClient::FileMeta &meta,
                            int ttl_seconds = 0) {
  json js;
  js["filename"] = meta.filename;
  js["filesize"] = meta.size;
  js["checksum"] = meta.checksum;

  for (const auto &r : meta.replicas) {
    js["replicas"].push_back({{"node_ip", r.node_ip},
                              {"node_port", r.node_port},
                              {"filepath", r.filepath}});
  }

  std::string value = js.dump();

  // // 先执行 SET 命令
  redisReply *reply = (redisReply *)redisCommand(
      context_, "SET %s %s", meta.uuid.c_str(), value.c_str());

  if (!reply) {
    std::cerr << "redis SET Command failed :" << std::endl;
    return;
  }
  //只是把新的内存地址赋给了 reply
  //变量，之前分配的内存并没有被释放，这就造成了内存泄漏。
  freeReplyObject(reply);

  // 如果设置了 TTL，执行 EXPIRE 命令
  if (ttl_seconds > 0) {
    reply = (redisReply *)redisCommand(context_, "EXPIRE %s %d",
                                       meta.uuid.c_str(), ttl_seconds);
    if (!reply) {
      std::cerr << "redisCommand EXPIRE failed :" << std::endl;
      return;
    }

    std::cout << "EXPIRE reply type: " << reply->type
              << ", integer: " << reply->integer << std::endl;
    freeReplyObject(reply);
  }
}

MySQLClient::FileMeta RedisClient::getMetaData(const std::string &key) {
  dfs::MySQLClient::FileMeta meta;

  redisReply *reply =
      (redisReply *)redisCommand(context_, "GET %s", key.c_str());
  if (!reply) {
    std::cerr << "redisCommand failed :" << std::endl;
    return meta;
  }

  if (reply->type == REDIS_REPLY_NIL) {
    std::cerr << "[Redis] Cache miss: key not found" << std::endl;
    freeReplyObject(reply);
    return meta;
  }

  if (reply->type != REDIS_REPLY_STRING) {
    std::cerr << "[Redis] Unexpected type: " << reply->type << std::endl;
    freeReplyObject(reply);
    return meta;
  }

  try {
    json js = json::parse(reply->str);
    meta.uuid = key;
    meta.filename = js["filename"];
    meta.size = js["filesize"];
    meta.checksum = js["checksum"];

    for (const auto &r : js["replicas"]) {
      dfs::MySQLClient::Replica replica;
      replica.filepath = r["filepath"];
      replica.node_ip = r["node_ip"];
      replica.node_port = r["node_port"];
      meta.replicas.push_back(replica);
    }
  } catch (...) {
    std::cerr << "[Redis JSON parse error >>>]" << std::endl;
  }
  std::string res = reply->str;
  freeReplyObject(reply);

  return meta;
}

bool RedisClient::removeCache(const std::string &key) {
  redisReply *reply =
      (redisReply *)redisCommand(context_, "DEL %s", key.c_str());

  if (!reply) {
    std::cerr << "Delete redisCache failed" << std::endl;
    return false;
  }
  return true;
}
} // namespace dfs