#include "gtest/gtest.h"

#include "experiment/experiment.hpp"

#include <iostream>

namespace orca
{
  namespace experiment
  {
    namespace
    {
      template<typename T>
      T f(T x[5])
      {
        T y1 = x[2] * (5.0 * x[0] + x[1]);
        T y2 = log(y1);
        T y = (y1 + x[3] * y2) * (y1 + y2);
        return y;
      }
    }

    TEST(test_experiment, simple)
    {
      // specializing to Number
      {
        Number x[5] = {1., 2., 3., 4., 5.};
        Number y = f(x);
        EXPECT_NEAR(y.calculate(), 797.751, 1.e-3);

        x[0].setValue(2.5);
        EXPECT_NEAR(y.calculate(), 2769.76, 1.e-2);
      }

      // // specializing to double
      // // would not compile, for log in the experiment namesapce is ambiguous
      // {
      //   double x[5] = {1., 2., 3., 4., 5.};
      //   double y = f(x);
      //   std::cout << y << std::endl;
      // }
    }
  }
}
