#pragma once

#include "aad/number.hpp"

namespace orca { namespace aad { namespace util {
  template<typename IT>
  inline void putOnTape(IT begin, IT end)
  {
    std::for_each(begin,
                  end,
                  [](Number& n)
                  { n.putOnTape(); });
  }

  template<typename It1, typename It2>
  inline void convert(It1 sourceBegin, It1 sourceEnd, It2 destinationBegin)
  {
    using destination_type_t = std::remove_reference_t<decltype(*destinationBegin)>;
    std::transform(sourceBegin,
                   sourceEnd,
                   destinationBegin,
                   [](const auto& source)
                   { return destination_type_t(source); });
  }
}}}
