#pragma once

#include <memory>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <array>
#include <list>
#include <iterator>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>

namespace orca
{
  using dbl_t = double;
  using dbl_vec_t = std::vector<dbl_t>;
  using dbl_vec_vec_t = std::vector<dbl_vec_t>;

  using string_t = std::string;
  using string_vec_t = std::vector<string_t>;

  using uint_t = unsigned int;
  using uint_vec_t = std::vector<uint_t>;

  using ulong_t = unsigned long;
  using ulong_vec_t = std::vector<ulong_t>;

  using int_t = int;
  using int_vec_t = std::vector<int_t>;
}
