#include "gtest/gtest.h"

#include "experiment/memory/matrix.hpp"
#include "experiment/memory/dist.hpp"

#include <iostream>
#include <cstdlib>
#include <chrono>

namespace orca { namespace test {
  TEST(Memory, MatrixProduct)
  {
    size_t rows = 1000;
    size_t cols = 1000;
    size_t n = 1000;
    experiment::memory::Matrix<dbl_t> a(rows, n);
    experiment::memory::Matrix<dbl_t> b(n, cols);
    for (size_t j = 0; j < n; ++j)
    {
      for (size_t i = 0; i < rows; ++i)
        a[i][j] = std::rand() * 1. / RAND_MAX;

      for (size_t i = 0; i < cols; ++i)
        b[j][i] = std::rand() * 1. / RAND_MAX;
    }

    experiment::memory::Matrix<dbl_t> c(rows, cols);

    // naive matrix multiplication
    {
      const auto start{std::chrono::steady_clock::now()};
      experiment::memory::naiveMatrixMultiplication(a, b, c);
      const auto end{std::chrono::steady_clock::now()};
      const std::chrono::duration<double> elapsed_seconds{end - start};
      std::cout << "Naive matrix multiplication: " << elapsed_seconds.count() << "s\n";
    }

    // smart, no vectorization
    {
      const auto start{std::chrono::steady_clock::now()};
      experiment::memory::smartMatrixMultiplication(a, b, c);
      const auto end{std::chrono::steady_clock::now()};
      const std::chrono::duration<double> elapsed_seconds{end - start};
      std::cout << "Smart matrix multiplication: " << elapsed_seconds.count() << "s\n";
    }
  }

  TEST(Memory, Distribution)
  {
    size_t n = 5000000;
    dbl_vec_t data(n);
    srand(12345);

    std::generate(data.begin(),
                  data.end(),
                  [](){ return rand() * 1. / RAND_MAX; });

    dbl_vec_t knots = {.1, .15, .2, .21, .25, .35, .4, .5, .55,
                       .6, .7, .75, .8, .85, .9, .95};

    {
      const auto start{std::chrono::steady_clock::now()};
      int_vec_t result = experiment::memory::dist(data, knots);
      const auto end{std::chrono::steady_clock::now()};
      const std::chrono::duration<double> elapsed_seconds{end - start};
      std::cout << "Serial distribution calculation: " << elapsed_seconds.count() << "s\n";

      std::cout << "result: \n";
      std::for_each(result.cbegin(),
                    result.cend(),
                    [=](int i){ std::cout << i * 1. / n << "\n"; });
    }
    {
      const auto start{std::chrono::steady_clock::now()};
      int_vec_t result = experiment::memory::parallelDist(data, knots);
      const auto end{std::chrono::steady_clock::now()};
      const std::chrono::duration<double> elapsed_seconds{end - start};
      std::cout << "Parallel distribution calculation: " << elapsed_seconds.count() << "s\n";

      std::cout << "result: \n";
      std::for_each(result.cbegin(),
                    result.cend(),
                    [=](int i){ std::cout << i * 1. / n << "\n"; });
    }
  }
}}
