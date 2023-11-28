#pragma once

#include "simulation/simulation.hpp"

namespace orca { namespace simulation {
  class RandomNumberGenerator
  {
  public:
    virtual ~RandomNumberGenerator(void) = default;
  public:
    virtual void init(size_t simDimension) = 0;

    virtual void nextUniform(dbl_vec_t& uniformVector) = 0;
    virtual void nextGaussian(dbl_vec_t& gaussianVector) = 0;

    virtual rng_ptr_t clone(void) const = 0;

    virtual size_t simDimension(void) const = 0;
  };
}}
