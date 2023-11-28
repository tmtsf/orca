#pragma once

#include "simulation/simulation.hpp"

namespace orca { namespace simulation {
  template<typename T>
  class Product
  {
  public:
    virtual ~Product(void) = default;
  public:
    virtual const time_vec_t& timeline(void) const = 0;
    virtual const sample_def_vec_t& defline(void) const = 0;

    virtual const string_vec_t& payoffLabels(void) const = 0;

    virtual void payoffs(const scenario_t<T>& path,
                         std::vector<T>& payoffs) const = 0;

    virtual product_ptr_t clone(void) const = 0;
  };
}}
