#pragma once

#include <string>
namespace dfs {
class FileManager {
public:
  //保存到磁盘。并返回完整路径
  static std::string saveFile(const std::string &filepath,
                              const std::string &filename,
                              const std::string &data);
  static size_t getFileSize(const std::string &data);
  static std::string readFile(const std::string &filename);
};
} // namespace dfs