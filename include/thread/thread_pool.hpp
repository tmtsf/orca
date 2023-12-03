#pragma once

#include "common/common.hpp"
#include "thread/concurrent_queue.hpp"

namespace orca { namespace thread {
  using namespace std::chrono_literals;

  class ThreadPool {
  private:
    // make the constructor private, ensuring only one instance
    ThreadPool() :
      m_Active(false),
      m_Interrupt(false)
    {}
  public:
    using task_t = std::packaged_task<bool(void)>;
    using future_t = std::future<bool>;

    static ThreadPool& getInstance() {
      return m_TheInstance;
    }

    // forbid copy and move
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    ~ThreadPool() {
      stop();
    }

    void start(std::size_t n = std::thread::hardware_concurrency() - 1) {
      if (!m_Active) {
        m_Threads.reserve(n);
        for (auto i = 0; i < n; ++i)
          m_Threads.emplace_back(&ThreadPool::threadFunc, this, i + 1);

        m_Active = true;
      }
    }

    template<typename Callable>
    future_t spawn(Callable c) {
      task_t t(std::move(c));
      future_t f = t.get_future();
      m_Q.push(std::move(t));
      return f;
    }

    void threadFunc(std::size_t index) {
      m_Index = index;

      task_t t;
      while (!m_Interrupt) {
        m_Q.pop(t);
        if (!m_Interrupt)
          t();
      }
    }

    bool activeWait(const future_t& f) {
      task_t t;
      bool b = false;

      while (f.wait_for(0s) != std::future_status::ready) {
        if (m_Q.tryPop(t)) {
          t();
          b = true;
        } else {
          f.wait();
        }
      }

      return b;
    }

    std::size_t numberOfThreads() const {
      return m_Threads.size();
    }

    static std::size_t getIndex() {
      return m_Index;
    }
  private:
    void stop() {
      if (m_Active) {
        m_Interrupt = true;
        m_Q.interrupt();
        std::for_each(m_Threads.begin(),
                      m_Threads.end(),
                      std::mem_fn(&std::thread::join));

        m_Threads.clear();

        m_Q.clear();
        m_Q.resetInterrupt();

        m_Active = false;
        m_Interrupt = false;
      }
    }
  private:
    static ThreadPool m_TheInstance;
    static thread_local std::size_t m_Index;
    std::vector<std::thread> m_Threads;
    ConcurrentQueue<task_t> m_Q;
    bool m_Active;
    bool m_Interrupt;
  };
}}
