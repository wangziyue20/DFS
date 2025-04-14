#include "heartbeat_client.h"
#include <muduo/net/EventLoop.h>
#include <thread>

int main() {
  muduo::net::EventLoop loop;

  std::string ip = "127.0.0.1";
  dfs::HeartbeatClient client(&loop, ip, 9000, 1);

  std::thread client_thread([&client]() {
    client.start();
    std::this_thread::sleep_for(std::chrono::seconds(20));
    client.stop();
  });

  loop.loop();

  client_thread.join();

  return 0;
}