#pragma once

#include "simulation/simulation.hpp"
#include "aad/number.hpp"

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

    virtual model_ptr_t<T> clone(void) const = 0;

    virtual const std::vector<T*>& parameters(void) = 0;
    virtual const string_vec_t& parameterLabels(void) const = 0;

    size_t numParams(void) const
    {
      return const_cast<Model*>(this)->parameters().size();
    }

    void putParametersOnTape(void)
    {
      putParametersOnTape<T>();
    }
  private:
    template<typename U>
    void putParametersOnTape()
    {
      // no-op for non-Number types
    }
    template<>
    void putParametersOnTape<aad::number_t>()
    {
      const auto& params = parameters();
      for (auto param : params)
        param->putOnTape();
    }
  };
}}
