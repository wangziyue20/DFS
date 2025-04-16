#include "calculateSHA.h"

#include <iostream>

namespace dfs {
std::string calculateSHA256(const std::string &path) {
  EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
  if (!md_ctx) {
    std::cerr << "Failed to create EVP_MD_CTX >>>" << std::endl;
    return "";
  }

  if (!EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL)) {
    EVP_MD_CTX_free(md_ctx);
    std::cerr << "Failed to initialize digest >>>" << std::endl;
    return "";
  }

  std::ifstream file(path, std::ios::binary);
  if (!file) {
    EVP_MD_CTX_free(md_ctx);
    std::cerr << "Failed to open file >>>" << std::endl;
    return "";
  }

  char buffer[1024];
  while (file.read(buffer, sizeof(buffer))) {
    if (!EVP_DigestUpdate(md_ctx, buffer, file.gcount())) {
      EVP_MD_CTX_free(md_ctx);
      std::cerr << "Failed to update disgest >>>" << std::endl;
      return "";
    }
  }

  // 处理未满缓冲区的最后一段
  if (file.gcount() > 0) {
    if (!EVP_DigestUpdate(md_ctx, buffer, file.gcount())) {
      EVP_MD_CTX_free(md_ctx);
      std::cerr << "Failed to update digest (tail block) >>>" << std::endl;
      return "";
    }
  }

  unsigned char md_value[EVP_MAX_MD_SIZE];
  unsigned int md_len;
  if (!EVP_DigestFinal_ex(md_ctx, md_value, &md_len)) {
    EVP_MD_CTX_free(md_ctx);
    std::cerr << "Failed to update digest (tail block) >>>" << std::endl;
    return "";
  }

  EVP_MD_CTX_free(md_ctx);

  std::stringstream ss;
  for (unsigned int i = 0; i < md_len; ++i) {
    ss << std::setw(2) << std::setfill('0') << std::hex << (int)md_value[i];
  }

  return ss.str(); // 返回十六进制字符串
}
} // namespace dfs