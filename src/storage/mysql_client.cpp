#include "mysql_client.h"

#include <iostream>

namespace dfs {
MySQLClient::MySQLClient() {
  connection_ = mysql_init(nullptr);
  if (!connection_) {
    throw std::runtime_error("mysql_init failed");
  }

  if (!mysql_real_connect(connection_, "127.0.0.1", "root", "123456", "metadb",
                          3306, nullptr, 0)) {
    mysql_close(connection_);
    throw std::runtime_error("mysql_real_connect failed");
  }
}

MySQLClient::~MySQLClient() {
  if (connection_) {
    mysql_close(connection_);
  }
}
void MySQLClient::insertMetaData(const FileMeta &file) {
  char query[1024];
  snprintf(query, sizeof(query),
           "INSERT INTO file_metadata (id, filename, size, checksum) VALUES "
           "('%s','%s','%ld', '%s')",
           file.uuid.c_str(), file.filename.c_str(), file.size,
           file.checksum.c_str());

  if (mysql_query(connection_, query)) {
    std::cerr << "Insert file_metadata failed: " << mysql_error(connection_)
              << std::endl;
    return;
  }

  for (auto &replica : file.replicas) {
    snprintf(query, sizeof(query),
             "INSERT INTO file_replicas(file_id, node_ip, node_port, filepath) "
             "VALUES ('%s', '%s', '%d','%s')",
             file.uuid.c_str(), replica.node_ip.c_str(), replica.node_port,
             replica.filepath.c_str());

    if (mysql_query(connection_, query)) {
      std::cerr << "Insert replica failed: " << mysql_error(connection_)
                << std::endl;
      return;
    }
  }
}

MySQLClient::FileMeta MySQLClient::getMetaData(const std::string &id) {
  FileMeta filemeta;

  char query[1024];
  snprintf(query, sizeof(query),
           "SELECT filename, size , checksum FROM "
           "file_metadata WHERE id "
           "= '%s'",
           id.c_str());

  if (mysql_query(connection_, query)) {
    std::cerr << "getMetaData failed:>>>" << mysql_error(connection_)
              << std::endl;
    return filemeta;
  }

  MYSQL_RES *result = mysql_store_result(connection_);
  if (result == nullptr) {
    std::cerr << "mysql_store_result failed:>>> " << mysql_error(connection_)
              << std::endl;
    return filemeta;
  }

  MYSQL_ROW row = mysql_fetch_row(result);
  if (row != nullptr) {
    filemeta.filename = row[0] ? row[0] : "";
    filemeta.size = row[1] ? std::stoull(row[1]) : 0;
    filemeta.checksum = row[2] ? row[2] : 0;
  }
  mysql_free_result(result);

  //查询副本
  snprintf(query, sizeof(query),
           "SELECT filepath, node_ip, node_port FROM "
           "file_replicas WHERE file_id "
           "= '%s'",
           id.c_str());

  if (mysql_query(connection_, query)) {
    std::cerr << "get Replicas failed:>>>" << mysql_error(connection_)
              << std::endl;
    return filemeta;
  }

  result = mysql_store_result(connection_);
  if (result == nullptr) {
    std::cerr << "mysql_store_result failed:>>> " << mysql_error(connection_)
              << std::endl;
    return filemeta;
  }

  while ((row = mysql_fetch_row(result))) {
    Replica r;
    r.filepath = row[0];
    r.node_ip = row[1];
    r.node_port = std::stoi(row[2]);
    filemeta.replicas.push_back(r);
  }
  mysql_free_result(result);

  filemeta.uuid = id;
  return filemeta;
}

bool MySQLClient::deleteMetaData(const std::string &id) {
  char query[1024];
  snprintf(query, sizeof(query), "DELETE FROM file_replicas WHERE file_id='%s'",
           id.c_str());

  if (mysql_query(connection_, query)) {
    std::cerr << "DELETE FROM file_metadata failed: "
              << mysql_error(connection_) << std::endl;
    return false;
  }

  //删除file_metadata
  snprintf(query, sizeof(query), "DELETE FROM file_metadata WHERE id='%s'",
           id.c_str());

  if (mysql_query(connection_, query)) {
    std::cerr << "DELETE FROM file_metadata failed: "
              << mysql_error(connection_) << std::endl;
    return false;
  }
  return true;
}
} // namespace dfs