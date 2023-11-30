#pragma once

#include "math/util.hpp"

namespace orca { namespace numeric {
  //  Normal density
  inline dbl_t normalPDF(const dbl_t x)
  {
      return (x < -10.0 || x > 10.0) ? 0.0 : exp(-0.5*x*x) / math::util::sqrtTwoPi();
  }

  //	Normal CDF (N in Black-Scholes)
  //  Zelen and Severo's approximation (1964)
  //  See https://en.wikipedia.org/wiki/Normal_distribution#Numerical_approximations_for_the_normal_CDF
  inline dbl_t normalCDF(const dbl_t x)
  {
    if (x < -10.0)
      return 0.0;
    if (x > 10.0)
      return 1.0;
    if (x < 0.0)
      return 1.0 - normalCDF(-x);

    static constexpr dbl_t p = 0.2316419;
    static constexpr dbl_t b1 = 0.319381530;
    static constexpr dbl_t b2 = -0.356563782;
    static constexpr dbl_t b3 = 1.781477937;
    static constexpr dbl_t b4 = -1.821255978;
    static constexpr dbl_t b5 = 1.330274429;

    const auto t = 1.0 / (1.0 + p*x);
    const auto pol = t*(b1 + t*(b2 + t*(b3 + t*(b4 + t*b5))));
    const auto pdf = normalPDF(x);
    return 1.0 - pdf * pol;
  }

  //	Inverse CDF (for generation of Gaussians out of Uniforms)
  //  Beasley-Springer-Moro algorithm
  //  Moro, The full Monte, Risk, 1995
  //  See Glasserman, Monte Carlo Methods in Financial Engineering, p 68
  inline dbl_t inverseNormalCDF(const dbl_t p)
  {
    const bool sup = p > 0.5;
    const dbl_t up = sup ? 1.0 - p : p;

    static constexpr dbl_t a0 = 2.50662823884;
    static constexpr dbl_t a1 = -18.61500062529;
    static constexpr dbl_t a2 = 41.39119773534;
    static constexpr dbl_t a3 = -25.44106049637;

    static constexpr dbl_t b0 = -8.47351093090;
    static constexpr dbl_t b1 = 23.08336743743;
    static constexpr dbl_t b2 = -21.06224101826;
    static constexpr dbl_t b3 = 3.13082909833;

    static constexpr dbl_t c0 = 0.3374754822726147;
    static constexpr dbl_t c1 = 0.9761690190917186;
    static constexpr dbl_t c2 = 0.1607979714918209;
    static constexpr dbl_t c3 = 0.0276438810333863;
    static constexpr dbl_t c4 = 0.0038405729373609;
    static constexpr dbl_t c5 = 0.0003951896511919;
    static constexpr dbl_t c6 = 0.0000321767881768;
    static constexpr dbl_t c7 = 0.0000002888167364;
    static constexpr dbl_t c8 = 0.0000003960315187;

    dbl_t x = up - 0.5;
    dbl_t r;

    if (fabs(x)<0.42)
    {
      r = x*x;
      r = x*(((a3*r + a2)*r + a1)*r + a0) / ((((b3*r + b2)*r + b1)*r + b0)*r + 1.0);
      return sup ? -r: r;
    }

    r = up;
    r = log(-log(r));
    r = c0 + r*(c1 + r*(c2 + r*(c3 + r*(c4 + r*(c5 + r*(c6 + r*(c7 + r*c8)))))));

    return sup? r: -r;
  }
}}
