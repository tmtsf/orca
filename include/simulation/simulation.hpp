#pragma once

#include "common/common.hpp"

namespace orca { namespace simulation {

  template<typename T>
  struct Sample;

  template<typename T>
  using scenario_t = std::vector<Sample<T>>;

  struct SampleDef;
  using sample_def_vec_t = std::vector<SampleDef>;

  using time_t = orca::dbl_t;
  using time_vec_t = std::vector<time_t>;

  template<typename T>
  class Product;

  template<typename T>
  using product_ptr_t = std::unique_ptr<Product<T>>;

  template<typename T>
  class Model;

  template<typename T>
  using model_ptr_t = std::unique_ptr<Model<T>>;

  class RandomNumberGenerator;
  using rng_ptr_t = std::unique_ptr<RandomNumberGenerator>;
}}
