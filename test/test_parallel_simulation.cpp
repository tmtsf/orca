#include "gtest/gtest.h"

#include "simulation/rng/sobol.hpp"
#include "simulation/model/bs.hpp"
#include "simulation/product/euro_option.hpp"
#include "simulation/util.hpp"

#include <iostream>

namespace orca { namespace test {
  TEST(ParallelSimulation, EuropeanOption)
  {
    double spot = 100.;
    double discount = .03;
    double dividend = .02;
    double vol = .2;

    auto model = simulation::model::BlackScholesModel<double>(spot,
                                                              vol,
                                                              false,
                                                              discount,
                                                              dividend);

    double strike = 101.;
    double expiry = 1.;
    double settlement = 1. + 2./365.;
    auto option = simulation::product::EuropeanOption<double>(strike, expiry, settlement);

    simulation::rng::Sobol rng;
    size_t numPaths = std::pow(2, 26) - 1;
    auto results = simulation::parallelSimulate(model, option, rng, numPaths);

    double sum(0.);
    for (const auto& path : results)
    {
      for (const auto& result : path)
      {
        sum += result;
      }
    }

    std::cout << sum / numPaths << std::endl;
  }
}}
