#include "gtest/gtest.h"

#include "aad/number.hpp"

#include <iostream>

namespace orca { namespace test {
  template<typename T>
  struct Multiplier
  {
    T m_Multipier;

    Multiplier(aad::value_t m) :
      m_Multipier(m)
    { }

    T operator()(T y) const
    {
      return m_Multipier * y;
    }
  };

  TEST(AAD, Const_Incorrect)
  {
    aad::Number::m_Tape->rewind();

    Multiplier<aad::Number> doubler(2.);
    aad::Number y(5.);

    aad::Number z = doubler(y);
    z.propagateToStart();

    EXPECT_EQ(z.value(), 10.);
    EXPECT_EQ(y.adjoint(), 2.);
    EXPECT_EQ(doubler.m_Multipier.adjoint(), 5.);
  }

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

    template<typename T>
    T g(T x[4])
    {
      double dt = .5;
      aad::Number mu = x[2] - x[3];
      aad::Number drift = (mu - .5 * x[1] * x[1]) * dt;
      aad::Number stdDev = x[1] * std::sqrt(dt);
      aad::Number y = x[0] * exp(-x[3] * dt) * exp(drift + stdDev * (-.03));

      return y;
    }
  }

  TEST(AAD, Intrumentation)
  {
    aad::Number::m_Tape->rewind();

    aad::Number x[5] = {aad::Number{1.}, aad::Number{2.}, aad::Number{3.}, aad::Number{4.}, aad::Number{5.}};
    aad::Number y = f(x);
    y.propagateToStart();

    for (size_t i = 0; i < 5; ++i)
    {
      std::cout << "x[" << i << "] = " << x[i].adjoint() << std::endl;
    }
  }

  namespace {

  }

  TEST(AAD, Bumping)
  {
    aad::Number::m_Tape->rewind();

    aad::Number x[4] = {aad::Number{100.},
                        aad::Number{.2},
                        aad::Number{.03},
                        aad::Number{.02}};
    aad::Number y = g(x);
    y.propagateToStart();

    std::vector<double> adjoints(4);
    for (size_t i = 0; i < 4; ++i)
      adjoints[i] = x[i].adjoint();

    double bump = 1e-5;
    std::vector<double> bumpedAdjoints(4);
    for (size_t i = 0; i < 4; ++i)
    {
      x[i] += bump;
      aad::Number yBumped = g(x);
      bumpedAdjoints[i] = (yBumped.value() - y.value()) / bump;
      x[i] -= bump;
    }

    for (size_t i = 0; i < 4; ++i)
    {
      std::cout << adjoints[i] << "\t" << bumpedAdjoints[i] << std::endl;
    }
  }
}}
