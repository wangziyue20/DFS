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
           "INSERT INTO file_metadata (id, filename, filepath, size, node_ip, "
           "node_port) VALUES "
           "('%s','%s', "
           "'%s', "
           "'%ld', '%s', '%d')",
           file.uuid.c_str(), file.filename.c_str(), file.filepath.c_str(),
           file.size, file.node_ip.c_str(), file.node_port);

  if (mysql_query(connection_, query)) {
    std::cerr << "Insert failed: " << mysql_error(connection_) << std::endl;
  }
}

MySQLClient::FileMeta MySQLClient::getMetaData(const std::string &id) {
  FileMeta filemeta;

  char query[1024];
  snprintf(query, sizeof(query),
           "SELECT filename, filepath, size, node_ip, node_port FROM "
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
    filemeta.filepath = row[1] ? row[1] : "";
    filemeta.size = row[2] ? std::stoull(row[2]) : 0;
    filemeta.node_ip = row[3] ? row[3] : "";
    filemeta.node_port = row[4] ? std::stoi(row[4]) : 0;
  }
  filemeta.uuid = id;
  return filemeta;
}
} // namespace dfs