
#pragma once

#include "simulation/random_number_generator.hpp"
#include "numeric/gaussian.hpp"


namespace orca { namespace simulation { namespace rng {
  class Sobol : public RandomNumberGenerator
  {
  public:
    Sobol(void);
  public:
    virtual void init(size_t simDimension) override;
    virtual void nextUniform(dbl_vec_t& uniformVector) override;
    virtual void nextGaussian(dbl_vec_t& gaussianVector) override;
    virtual rng_ptr_t clone(void) const override;
    virtual size_t simDimension(void) const override;
  private:
    void reset(void);
    void next(void);
    void skipTo(uint_t b);
  private:
    size_t      m_Dimension;
    uint_vec_t  m_State;
    uint_t     m_Index;
    const uint_t* const * m_JKDir;
  };
}}}
