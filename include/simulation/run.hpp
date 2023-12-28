#pragma once

#include "simulation/sample.hpp"
#include "simulation/model.hpp"
#include "simulation/product.hpp"
#include "simulation/random_number_generator.hpp"
#include "simulation/results.hpp"
#include "thread/thread_pool.hpp"
#include "aad/number.hpp"
#include "aad/util.hpp"

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

  inline dbl_vec_vec_t parallelSimulate(const Model<dbl_t>& model,
                                        const Product<dbl_t>& product,
                                        const RandomNumberGenerator& rng,
                                        size_t numPaths)
  {
    const size_t BATCHSIZE = 128;

    auto m = model.clone();

    size_t numPayments = product.payoffLabels().size();
    dbl_vec_vec_t results(numPaths, dbl_vec_t(numPayments));

    m->allocate(product.timeline(), product.defline());
    m->init(product.timeline(), product.defline());

    // Allocate space for Gaussian vectors and paths, one for each thread
    thread::ThreadPool& pool = thread::ThreadPool::getInstance();
    pool.start();
    size_t numThreads = pool.numberOfThreads();
    dbl_vec_vec_t gaussianVector(numThreads + 1);
    std::vector<scenario_t<dbl_t>> paths(numThreads + 1);
    for (auto& gaussian : gaussianVector)
      gaussian.resize(m->simDimension());

    for (auto& path : paths)
    {
      util::allocatePath(product.defline(), path);
      util::initializePath(path);
    }

    // Build one random number generator per thread
    std::vector<rng_ptr_t> generators(numThreads + 1);
    for (auto& gen : generators)
    {
      gen = rng.clone();
      gen->init(m->simDimension());
    }

    std::vector<thread::ThreadPool::future_t> futures;
    futures.reserve(numPaths / BATCHSIZE + 1);

    size_t firstPath = 0;
    size_t pathsLeft = numPaths;
    while (pathsLeft > 0)
    {
      size_t pathsInTask = std::min(pathsLeft, BATCHSIZE);
      futures.push_back(pool.spawn(
                              [&, firstPath, pathsInTask]()
                              {
                                size_t index = pool.getIndex();

                                auto& gaussian = gaussianVector[index];
                                auto& path = paths[index];

                                auto& gen = generators[index];
                                gen->skipTo(firstPath);

                                for (size_t i = 0; i < pathsInTask; ++i)
                                {
                                  gen->nextGaussian(gaussian);
                                  m->generatePath(gaussian, path);
                                  product.payoffs(path, results[firstPath + i]);
                                }

                                return true;
                              }));

      pathsLeft -= pathsInTask;
      firstPath += pathsInTask;
    }

    for (auto& future : futures)
    {
      pool.activeWait(future);
    }

    return results;
  }

  static auto defaultAggregator = [](const aad::number_vec_t& v){ return v[0]; };

  template<typename F = decltype(defaultAggregator)>
  inline SimulationResults simulate(const Model<aad::number_t>& model,
                                    const Product<aad::number_t>& product,
                                    const RandomNumberGenerator& rng,
                                    size_t numPaths,
                                    const F& aggregator = defaultAggregator)
  {
    auto m = model.clone();
    auto r = rng.clone();

    scenario_t<aad::number_t> path;
    util::allocatePath(product.defline(), path);
    m->allocate(product.timeline(), product.defline());

    size_t numPayments = product.payoffLabels().size();
    const aad::number_ptr_coll_t& params = m->parameters();
    size_t numParams = params.size();

    // initialize the tape, put all the model parameters on it, and mark
    aad::Tape& tape = *aad::Number::m_Tape;
    tape.clear();
    m->putParametersOnTape();
    m->init(product.timeline(), product.defline());
    util::initializePath(path);
    tape.mark();

    r->init(m->simDimension());
    aad::number_vec_t payoffs(numPayments);
    dbl_vec_t gaussianVector(m->simDimension());

    SimulationResults results(numPaths, numPayments, numParams);
    for (size_t i = 0; i < numPaths; ++i)
    {
      tape.rewindToMark();

      r->nextGaussian(gaussianVector);
      m->generatePath(gaussianVector, path);
      product.payoffs(path, payoffs);
      aad::number_t result = aggregator(payoffs);

      result.propagateToMark();
      results.m_Aggregated[i] = double(result);
      aad::util::convert(payoffs.begin(), payoffs.end(), results.m_Payoffs[i].begin());
    }

    aad::Number::propagateMarkToStart();
    std::transform(params.begin(),
                   params.end(),
                   results.m_Risks.begin(),
                   [numPaths](const aad::number_ptr_t p)
                   { return p->adjoint() / numPaths; });
    tape.clear();

    return results;
  }
}}
