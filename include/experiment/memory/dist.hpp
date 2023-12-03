#pragma once

#include "common/common.hpp"

namespace orca { namespace experiment { namespace memory {
  int_vec_t dist(const dbl_vec_t& data,
                 const dbl_vec_t& knots)
  {
    size_t n = knots.size() + 1;
    int_vec_t result(n, 0);

    for (size_t i = 0; i < n; ++i)
    {
      dbl_t lb = (i == 0) ? -std::numeric_limits<dbl_t>::max() : knots[i - 1];
      dbl_t ub = (i == n - 1) ? std::numeric_limits<dbl_t>::max() : knots[i];

      // // version 1: manual loop
      // for (size_t j = 0; j < data.size(); ++j)
      //   result[i] += (lb < data[j] && data[j] <= ub);

      // // version 2: manual loop, with temporary variable, avoid cache pingpong
      // int_t count = 0;
      // for (size_t j = 0; j < data.size(); ++j)
      //   count += (lb < data[j] && data[j] <= ub);
      // result[i] = count;

      // version 3: STL algorithm
      result[i] = std::count_if(data.cbegin(),
                                data.cend(),
                                [=](dbl_t x){ return lb < x && x <= ub; });
    }

    return result;
  }

  int_vec_t parallelDist(const dbl_vec_t& data,
                         const dbl_vec_t& knots)
  {
    size_t n = knots.size() + 1;
    int_vec_t result(n, 0);
    std::vector<std::thread> threads(n);

    for (size_t i = 0; i < n; ++i)
    {
      threads[i] = std::thread([&, i]()
      {
        dbl_t lb = (i == 0) ? -std::numeric_limits<dbl_t>::max() : knots[i - 1];
        dbl_t ub = (i == n - 1) ? std::numeric_limits<dbl_t>::max() : knots[i];

        // // version 1: manual loop
        // for (size_t j = 0; j < data.size(); ++j)
        //   result[i] += (lb < data[j] && data[j] <= ub);

        // // version 2: manual loop, with temporary variable, avoid cache pingpong
        // int_t count = 0;
        // for (size_t j = 0; j < data.size(); ++j)
        //   count += (lb < data[j] && data[j] <= ub);
        // result[i] = count;

        // version 3: STL algorithm
        result[i] = std::count_if(data.cbegin(),
                                  data.cend(),
                                  [=](dbl_t x){ return lb < x && x <= ub; });
      });
    }

    for (size_t i = 0; i < n; ++i)
      threads[i].join();

    return result;
  }
}}}
