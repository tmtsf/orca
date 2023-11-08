#include "aad/util.hpp"

namespace orca { namespace aad { namespace util {
  bool isZeroToMachineTolerance(dbl_t value)
  {
    return std::fabs(value) < std::numeric_limits<dbl_t>::epsilon();
  }
}}}
