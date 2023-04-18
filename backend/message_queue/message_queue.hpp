#pragma once

#include <sys/ipc.h>
#include <sys/msg.h>

#include <optional>

#define MSG_SIZE 22
#define PERM 0666

namespace MQ {

enum Waiting { Wait, DontWait };

class MessageQueue {
 public:
  MessageQueue() = default;

  explicit MessageQueue(key_t key);

  MessageQueue(const MessageQueue& other) = default;

  ~MessageQueue() = default;

  MessageQueue& operator=(const MessageQueue& other) = default;

  std::optional<int> Receive(int64_t msg_type, Waiting wait);

  void Send(int message, int64_t msg_type);

  void DeleteQueue() noexcept;

 private:
  int descriptor_;
  struct MsgBuf {
    int64_t type;
    char msg[MSG_SIZE];
  };
};

}  // namespace MQ