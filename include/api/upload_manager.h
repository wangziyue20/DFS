#pragma once

#include "crow.h"

namespace dfs {
class UploadManager {
public:
  static crow::response uploaderHandler(const crow::request &req);
};
} // namespace dfs