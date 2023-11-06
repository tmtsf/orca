#pragma once

#include "common/common.hpp"

namespace orca { namespace experiment { namespace eager {
    class Node;
    class Number;

    using node_ptr_t = std::shared_ptr<Node>;
    using node_ptr_coll_t = std::vector<node_ptr_t>;

    class Visitor;

    using value_t = double;
    using value_map_t = std::unordered_map<size_t, value_t>;

    using adjoint_t = double;
    using adjoint_map_t = std::unordered_map<size_t, adjoint_t>;
} } }
