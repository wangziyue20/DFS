#include "file_manager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;

namespace dfs {
//保存到磁盘。并返回完整路径
std::string FileManager::saveFile(const std::string &filepath,
                                  const std::string &filename,
                                  const std::string &data) {
  std::string dir = filepath;
  if (!fs::exists(dir)) {
    fs::create_directories(dir);
    std::cout << "create dir" << dir << std::endl;
  }

  std::string fullpath = filepath + "/" + filename;

  std::ofstream out(fullpath, std::ios::binary);
  if (!out) {
    std::cerr << "open file failed>>>" << std::endl;
    return "";
  }

  out.write(data.c_str(), data.size());
  out.close();

  return fullpath;
}

size_t FileManager::getFileSize(const std::string &data) { return data.size(); }

std::string FileManager::readFile(const std::string &path) {
  std::cout << "full path :" + path << std::endl;

  std::ifstream in(path, std::ios::binary);

  if (!in) {
    std::cerr << "open file failed >>> " << std::endl;
    return "";
  }

  //获取文件大小
  in.seekg(0, std::ios::end);
  size_t filesize = in.tellg();
  in.seekg(0, std::ios::beg);

  //将文件内容保存到字符串
  std::string data(filesize, '\0');
  in.read(&data[0], filesize);
  in.close();

  return data;
}

bool FileManager::deleteFile(const std::string &path) {
  return fs::remove(path) == 0;
}
} // namespace dfs