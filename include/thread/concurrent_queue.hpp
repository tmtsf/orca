#pragma once

#include "common/common.hpp"

namespace orca { namespace thread {
  template<typename T>
  class ConcurrentQueue {
  public:
    ConcurrentQueue() :
      m_Interrupt(false)
    { }
    ~ConcurrentQueue() {
      interrupt();
    }
    bool empty() const {
      std::lock_guard<std::mutex> lock(m_Mutex);
      return m_Q.empty();
    }
    bool tryPop(T& t) {
      std::lock_guard<std::mutex> lock(m_Mutex);
      if (m_Q.empty())
        return false;

      t = std::move(m_Q.front());
      m_Q.pop();
      return true;
    }
    void push(T t) {
      std::lock_guard<std::mutex> lock(m_Mutex);
      m_Q.push(std::move(t));
      m_CV.notify_one();
    }
    bool pop(T& t) {
      std::unique_lock<std::mutex> lock(m_Mutex);
      m_CV.wait(lock, [this](){ return !m_Q.empty() || m_Interrupt; });

      if (m_Interrupt)
        return false;

      t = std::move(m_Q.front());
      m_Q.pop();
      return true;
    }
    void interrupt() {
      std::lock_guard<std::mutex> lock(m_Mutex);
      m_Interrupt = true;
      m_CV.notify_all();
    }
    void resetInterrupt() {
      m_Interrupt = false;
    }
    void clear() {
      std::queue<T> temp;
      std::swap(m_Q, temp);
    }
  private:
    std::mutex m_Mutex;
    std::queue<T> m_Q;
    std::condition_variable m_CV;
    bool m_Interrupt;
  };
}}
