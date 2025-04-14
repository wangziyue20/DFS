#pragma once

#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/http/HttpRequest.h>
#include <muduo/net/http/HttpResponse.h>
#include <muduo/net/http/HttpServer.h>

namespace dfs {
class UploadServer {
public:
  UploadServer(int port);
  void start();

private:
  muduo::net::EventLoop loop_;
  muduo::net::HttpServer server_;
  void onRequest(const muduo::net::HttpRequest &req,
                 muduo::net::HttpResponse *resp);
};
} // namespace dfs