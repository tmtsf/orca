#include "gtest/gtest.h"

#include "experiment/lazy/number.hpp"
#include "experiment/lazy/node.hpp"

#include "experiment/eager/number.hpp"
#include "experiment/eager/node.hpp"

#include <iostream>

namespace orca
{
  namespace test
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

    // TEST(calculation_graph, log)
    // {
    //   // specializing to Number
    //   {
    //     Number x[5] = {1., 2., 3., 4., 5.};
    //     Number y = f(x);
    //     std::cout << "Printing calculation log for expression: \n"
    //               << "y1 = x[2] * (5.0 * x[0] + x[1]);\n"
    //               << "y2 = log(y1);\n"
    //               << "y = (y1 + x[3] * y2) * (y1 + y2);\n"
    //               << "with x[5] = {1., 2., 3., 4., 5.};\n\n";
    //     y.printLog();

    //     x[0].setValue(2.5);
    //     std::cout << "\n\n"
    //               << "Printing calculation log for expression: \n"
    //               << "y1 = x[2] * (5.0 * x[0] + x[1]);\n"
    //               << "y2 = log(y1);\n"
    //               << "y = (y1 + x[3] * y2) * (y1 + y2);\n"
    //               << "with x[5] = {2.5, 2., 3., 4., 5.};\n\n";
    //     y.printLog();
    //   }
    // }

    TEST(lazy, evaluation)
    {
      // specializing to Number
      {
        experiment::lazy::Number x[5] = {1., 2., 3., 4., 5.};
        experiment::lazy::Number y = f(x);
        try
        {
          dbl_t value = 797.751;
          EXPECT_NEAR(y.calculate(), value, 1.e-3);
          const auto& adjoints = y.adjoints();

          const dbl_vec_t& expected = {950.736, 190.147, 443.677, 73.2041, 0.};
          for (size_t i = 1; i <= 5; ++i)
          {
            dbl_t adjoint = adjoints.count(i) ? adjoints.at(i) : 0.;
            EXPECT_NEAR(adjoint, expected[i - 1], 1.e-3);
            // std::cout << i << ": " << adjoint << std::endl;
          }

          // x[0].setValue(2.5);
          // EXPECT_NEAR(y.calculate(), 2769.76, 1.e-2);
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

    TEST(eager, evaluation)
    {
      // specializing to Number
      {
        experiment::eager::Number x[5] = {1., 2., 3., 4., 5.};
        experiment::eager::Number y = f(x);
        try
        {
          dbl_t value = 797.751;
          EXPECT_NEAR(y.result(), value, 1.e-3);

          y.propagateAdjoints();
          const dbl_vec_t& expected = {950.736, 190.147, 443.677, 73.2041, 0.};
          for (size_t i = 0; i < 5; ++i)
          {
            EXPECT_NEAR(x[i].adjoint(), expected[i], 1.e-3);
            // std::cout << i << ": " << adjoint << std::endl;
          }

          // x[0].setValue(2.5);
          // EXPECT_NEAR(y.calculate(), 2769.76, 1.e-2);
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
