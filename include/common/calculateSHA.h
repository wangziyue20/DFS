#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/evp.h>
#include <sstream>

namespace dfs {
std::string calculateSHA256(const std::string &path);
} // namespace dfs