#include "thread/thread_pool.hpp"

namespace orca { namespace thread {
  ThreadPool ThreadPool::m_TheInstance;

  thread_local std::size_t ThreadPool::m_Index = 0;
}}
