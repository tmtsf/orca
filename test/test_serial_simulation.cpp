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
    size_t numPaths = std::pow(2, 14) - 1;

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
    aad::number_t discount{.03};
    aad::number_t dividend{.02};
    aad::number_t vol{.2};

    auto model = simulation::model::BlackScholesModel<aad::number_t>(spot,
                                                                     vol,
                                                                     false,
                                                                     discount,
                                                                     dividend);

    double strike{101.};
    double expiry{1.};
    double settlement{1. + 2./365.};
    auto option = simulation::product::EuropeanOption<aad::number_t>(strike, expiry, settlement);

    simulation::rng::Sobol rng;
    size_t numPaths = std::pow(2, 20) - 1;

    const auto start{std::chrono::steady_clock::now()};
    auto results = simulation::simulate(model, option, rng, numPaths);
    const auto end{std::chrono::steady_clock::now()};
    const std::chrono::duration<double> elapsed_seconds{end - start};
    std::cout << "Serial simulation: " << elapsed_seconds.count() << "s\n";

    aad::number_t sum(0.);
    for (const auto& path : results.m_Payoffs)
    {
      for (const auto& result : path)
      {
        sum += result;
      }
    }

    std::cout << "European option price: " << sum.value() / numPaths << std::endl;
    std::cout << "European option risks: " << std::endl;

    for (const auto& risk : results.m_Risks)
    {
      std::cout << risk << std::endl;
    }
  }
}}
