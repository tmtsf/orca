#pragma once

#include "common/common.hpp"

namespace orca { namespace experiment { namespace eager {
  class Node;
  class Number;

  using value_t = double;
  using adjoint_t = double;

  using node_ptr_t = Node*;
  using node_ptr_coll_t = std::vector<node_ptr_t>;

  using tape_t = std::vector<std::unique_ptr<Node>>;
} } }
