#pragma once

#include "simulation/sample.hpp"
#include "simulation/model.hpp"
#include "simulation/product.hpp"
#include "simulation/random_number_generator.hpp"

namespace orca { namespace simulation {
  namespace util {
    template<typename T>
    inline void allocatePath(const sample_def_vec_t& defline,
                            scenario_t<T>& path)
    {
      path.resize(defline.size());
      for (size_t i = 0; i < defline.size(); ++i)
        path[i].allocate(defline[i]);
    }

    template<typename T>
    inline void initializePath(scenario_t<T>& path)
    {
      for (auto& sample : path)
        sample.initialize();
    }
  }

  inline dbl_vec_vec_t simulate(const Model<dbl_t>& model,
                                const Product<dbl_t>& product,
                                const RandomNumberGenerator& rng,
                                size_t numPaths)
  {
    auto m = model.clone();
    auto r = rng.clone();

    size_t numPayments = product.payoffLabels().size();
    dbl_vec_vec_t results(numPaths, dbl_vec_t(numPayments));

    m->allocate(product.timeline(), product.defline());
    m->init(product.timeline(), product.defline());

    r->init(m->simDimension());

    dbl_vec_t gaussianVector(m->simDimension());

    scenario_t<dbl_t> path;
    util::allocatePath(product.defline(), path);
    util::initializePath(path);

    for (size_t i = 0; i < numPaths; ++i)
    {
      r->nextGaussian(gaussianVector);
      m->generatePath(gaussianVector, path);
      product.payoffs(path, results[i]);
    }

    return results;
  }

}}
