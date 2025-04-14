#pragma once

#include "crow.h"
namespace dfs {
class DownloadManager {
public:
  static crow::response downloadById(const std::string id);
};
} // namespace dfs