#include "gtest/gtest.h"

#include "thread/thread_pool.hpp"

#include <iostream>

namespace orca { namespace test {
  TEST(ThreadPool, run)
  {
    orca::thread::ThreadPool& pool = orca::thread::ThreadPool::getInstance();
    pool.start();

    std::size_t numTasks = 100;
    std::vector<orca::thread::ThreadPool::future_t> futures(numTasks);
    for (auto i = 0; i < numTasks; ++i)
    {
      futures[i] = pool.spawn([&, i]()
                              {
                                int seconds = std::rand() % 3;
                                std::cout << "Inside task " << i << ", wait " << seconds << " seconds\n";
                                std::this_thread::sleep_for(std::chrono::seconds(seconds));
                                return true;
                              });
    }

    for (auto i = 0; i < numTasks; ++i)
    {
      pool.activeWait(futures[i]);
    }
  }
}}
