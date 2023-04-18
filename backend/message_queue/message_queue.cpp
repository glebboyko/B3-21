#include "message_queue.hpp"

using namespace MQ;

MessageQueue::MessageQueue(key_t key) {
  descriptor_ = msgget(key, PERM);
  if (descriptor_ == -1) {
    if (errno == ENOENT) {
      descriptor_ = msgget(key, IPC_CREAT | PERM);
      if (descriptor_ < 0) {
        throw errno;
      }
    } else {
      throw errno;
    }
  }
}

std::optional<int> MessageQueue::Receive(int64_t msg_type, Waiting wait) {
  MsgBuf msg;
  int flag = wait == Wait ? 0 : IPC_NOWAIT;
  if (msgrcv(descriptor_, &msg, MSG_SIZE, msg_type, flag) < 0) {
    if (errno == ENOMSG) {
      return {};
    }
    throw errno;
  }
  int result;
  sscanf(msg.msg, "%d", &result);
  return result;
}

void MessageQueue::Send(int message, int64_t msg_type) {
  MsgBuf msg_buf;
  sprintf(msg_buf.msg, "%d", message);
  msg_buf.type = msg_type;
  if (msgsnd(descriptor_, &msg_buf, strlen(msg_buf.msg) + 1, 0) < 0) {
    throw errno;
  }
}

void MessageQueue::DeleteQueue() noexcept {
  msgctl(descriptor_, IPC_RMID, nullptr);
}