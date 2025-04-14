#include "utils.h"

namespace dfs {
crow::response forwardRequest(const std::string &url, const crow::request &req,
                              const std::vector<std::string> &headers = {});

std::string extractNodeUrlFromPath(const std::string &path) {}
} // namespace dfs