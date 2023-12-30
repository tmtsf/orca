#include "gtest/gtest.h"

#include "simulation/rng/sobol.hpp"
#include "simulation/model/bs.hpp"
#include "simulation/product/euro_option.hpp"
#include "simulation/run.hpp"

#include <iostream>

namespace orca { namespace test {
  TEST(SerialSimulation, EuropeanOption)
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
    size_t numPaths = std::pow(2, 18) - 1;

    const auto start{std::chrono::steady_clock::now()};
    auto results = simulation::simulate(model, option, rng, numPaths);
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "Serial simulation: " << elapsed_seconds.count() << "s\n";

    double sum(0.);
    for (const auto& path : results)
    {
      for (const auto& result : path)
      {
        sum += result;
      }
    }

    std::cout << "European option price: " << sum / numPaths << std::endl;
  }

  TEST(SerialSimulation, EuropeanOptionAAD)
  {
    aad::number_t spot{100.};
    aad::number_t vol{.2};
    aad::number_t discount{.03};
    aad::number_t dividend{.02};

    auto model = simulation::model::BlackScholesModel<aad::number_t>(spot,
                                                                     vol,
                                                                     false,
                                                                     discount,
                                                                     dividend);

    double strike{101.};
    double expiry{1.};
    double settlement{expiry + 2. / 365.};
    auto option = simulation::product::EuropeanOption<aad::number_t>(strike, expiry, settlement);

    simulation::rng::Sobol rng;
    size_t numPaths = std::pow(2, 18) - 1;

    const auto start{std::chrono::steady_clock::now()};
    auto results = simulation::simulate(model, option, rng, numPaths);
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "Serial simulation: " << elapsed_seconds.count() << "s\n";

    double sum(0.);
    for (const auto& result : results.m_Aggregated)
    {
      sum += result;
    }

    sum /= numPaths;
    std::cout << "European option price: " << sum << std::endl;
    std::cout << "European option risks: " << std::endl;

    for (const auto& risk : results.m_Risks)
    {
      std::cout << risk << std::endl;
    }

    {
      double bump = 1e-5;
      std::vector<double> params{spot.value(), vol.value(), discount.value(), dividend.value()};
      for (size_t i = 0; i < 4; ++i)
      {
        params[i] += bump;

        auto bumpedModel = simulation::model::BlackScholesModel<double>(params[0],
                                                                        params[1],
                                                                        false,
                                                                        params[2],
                                                                        params[3]);
        auto bumpedOption = simulation::product::EuropeanOption<double>(strike, expiry, settlement);

        simulation::rng::Sobol bumpedRNG;
        auto bumpedResults = simulation::simulate(bumpedModel, bumpedOption, bumpedRNG, numPaths);

        double bumpedSum(0.);
        for (const auto& path : bumpedResults)
        {
          for (const auto& result : path)
          {
            bumpedSum += result;
          }
        }

        bumpedSum /= numPaths;
        std::cout << "Parameter " << i << std::endl;
        std::cout << "Bumped value is: " << bumpedSum << std::endl;
        std::cout << "Bumped greek is: " << (bumpedSum - sum) / bump
                  << std::endl << std::endl;

        params[i] -= bump;
      }
    }
  }
}}
