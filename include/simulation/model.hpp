#pragma once

#include "simulation/simulation.hpp"

namespace orca { namespace simulation {
  template<typename T>
  class Model
  {
  public:
    virtual ~Model(void) = default;
  public:
    virtual void allocate(const time_vec_t& productTimeline,
                          const sample_def_vec_t& productDefline) = 0;
    virtual void init(const time_vec_t& productTimeline,
                      const sample_def_vec_t& productDefline) = 0;

    virtual size_t simDimension(void) const = 0;

    virtual void generatePath(const dbl_vec_t& gaussVector,
                              scenario_t<T>& path) const = 0;

    virtual model_ptr_t clone(void) const = 0;

    virtual const std::vector<T*>& parameters(void) = 0;
    virtual const std::vector<string_t>& parameterLabels(void) const = 0;

    size_t numParams(void) const
    {
      return const_cast<Model*>(this)->parameters().size();
    }
  };
}}
