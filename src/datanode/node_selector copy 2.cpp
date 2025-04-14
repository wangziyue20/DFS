#include "crow.h"
#include "node_selector.h"

#include <cstdio>
#include <curl/curl.h>
#include <iostream>
// #include <stdexcept>

namespace dfs {
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
  //将收到的数据追加到字符串中
  ((std::string *)userp)->append((char *)contents, size * nmemb);
  return size * nmemb;
}

NodeSelector::NodeSelector(const std::string &master_utl)
    : master_utl_(master_utl) {}

std::vector<NodeInfo> NodeSelector::fetchNodes() {
  std::vector<NodeInfo> nodes;

  CURL *curl = curl_easy_init();
  std::string response;

  curl_easy_setopt(curl, CURLOPT_URL, master_utl_.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
  CURLcode res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  if (res != CURLE_OK) {
    std::cerr << "Failed to fetch nodes\n";
    return nodes;
  }

  auto json = crow::json::load(response);
  if (!json) {
    std::cerr << "Invalid JSON from master\n";
    return nodes;
  }

  for (auto &node : json) {
    if (node.has("id") && node.has("ip") && node.has("port") &&
        node.has("path")) {
      nodes.emplace_back(
          static_cast<int>(node["id"].i()), std::string(node["ip"].s()),
          static_cast<int>(node["port"].i()), std::string(node["path"].s()));
    } else {
      std::cerr << "JSON has no element\n";
      return nodes;
    }
  }
  return nodes;
}
NodeInfo NodeSelector::select() {
  auto nodes = fetchNodes();

  if (nodes.empty()) {
    throw std::runtime_error("No available nodes >>>\n");
  }

  return nodes[rand() % nodes.size()];
}
} // namespace dfs