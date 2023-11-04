#include "gtest/gtest.h"

#include "experiment/number.hpp"
#include "experiment/node.hpp"

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

    TEST(calculation_graph, log)
    {
      // specializing to Number
      {
        Number x[5] = {1., 2., 3., 4., 5.};
        Number y = f(x);
        std::cout << "Printing calculation log for expression: \n"
                  << "y1 = x[2] * (5.0 * x[0] + x[1]);\n"
                  << "y2 = log(y1);\n"
                  << "y = (y1 + x[3] * y2) * (y1 + y2);\n"
                  << "with x[5] = {1., 2., 3., 4., 5.};\n\n";
        y.printLog();

        x[0].setValue(2.5);
        std::cout << "\n\n"
                  << "Printing calculation log for expression: \n"
                  << "y1 = x[2] * (5.0 * x[0] + x[1]);\n"
                  << "y2 = log(y1);\n"
                  << "y = (y1 + x[3] * y2) * (y1 + y2);\n"
                  << "with x[5] = {2.5, 2., 3., 4., 5.};\n\n";
        y.printLog();
      }
    }

    TEST(calculation_graph, evaluation)
    {
      // specializing to Number
      {
        Number x[5] = {1., 2., 3., 4., 5.};
        Number y = f(x);
        try
        {
          EXPECT_NEAR(y.calculate(), 797.751, 1.e-3);

          x[0].setValue(2.5);
          EXPECT_NEAR(y.calculate(), 2769.76, 1.e-2);
        }
        catch (const char* e)
        {
          std::cout << e << std::endl;
        }
        catch (...)
        {
          abort();
        }
      }
    }
  }
}
