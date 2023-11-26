#pragma once

#include "common/common.hpp"


namespace orca { namespace aad {
  class Node;
  class BlockList;
  class Tape;
  class Number;

  using value_t = dbl_t;
  using value_ptr_t = value_t*;

  using adjoint_t = dbl_t;
  using adjoint_ptr_t = adjoint_t*;
  using adjoint_ptr_coll_t = adjoint_ptr_t*;

  using derivative_t = dbl_t;
  using derivative_coll_t = derivative_t*;

  template<typename T, size_t BlockSize>
  using array_t = std::array<T, BlockSize>;

  template<typename T, size_t BlockSize>
  using array_list_t = std::list<array_t<T, BlockSize>>;
}}