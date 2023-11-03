#pragma once

#include "common/common.hpp"

namespace orca
{
  namespace experiment
  {
    class Node;
    class Number;

    using node_ptr_t = std::shared_ptr<Node>;
    using node_ptr_coll_t = std::vector<node_ptr_t>;

    template<typename R>
    class Visitor;
  }
}
