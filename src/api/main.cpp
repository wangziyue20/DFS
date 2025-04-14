#include "upload_server.h"

int main() {
  dfs::UploadServer server(8080);
  server.start();
  return 0;
}
