#include "math/util.hpp"

namespace orca { namespace math { namespace util {
  bool isZeroToMachineTolerance(dbl_t value)
  {
    return std::fabs(value) < std::numeric_limits<dbl_t>::epsilon();
  }

  bool areEqualToMachineTolerance(dbl_t p, dbl_t q)
  {
    return isZeroToMachineTolerance(std::fabs(p - q));
  }

  bool isPositive(dbl_t p)
  {
    return p > std::numeric_limits<dbl_t>::epsilon();
  }

  bool isLargerThanMachineTolerance(dbl_t p, dbl_t q)
  {
    return isPositive(p - q);
  }

  const dbl_t& epsilon(void)
  {
    static dbl_t eps = 1.e-8;
    return eps;
  }

  const dbl_t& pi(void)
  {
    static dbl_t p = 3.14159265358979323846;
    return p;
  }

  const dbl_t& sqrtTwoPi(void)
  {
    static dbl_t n = std::sqrt(2. * pi());
    return n;
  }

  const dbl_t& oneOverTwoPower32(void)
  {
    static dbl_t n = 2.3283064365387e-10;
    return n;
  }
}}}
