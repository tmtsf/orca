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
}}
