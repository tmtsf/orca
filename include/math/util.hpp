#pragma once

#include "common/common.hpp"

namespace orca { namespace math { namespace util {
  bool isZeroToMachineTolerance(dbl_t value);

  bool areEqualToMachineTolerance(dbl_t p, dbl_t q);

  bool isPositive(dbl_t p);

  bool isLargerThanMachineTolerance(dbl_t p, dbl_t q);

  const dbl_t& epsilon(void);

  const dbl_t& pi(void);

  const dbl_t& sqrtTwoPi(void);

  const dbl_t& oneOverTwoPower32(void);
}}}
