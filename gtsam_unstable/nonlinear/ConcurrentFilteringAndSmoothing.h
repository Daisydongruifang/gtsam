/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation, 
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    ConcurrentFilteringAndSmoothing.h
 * @brief   Base classes for the 'filter' and 'smoother' portion of the Concurrent
 *          Filtering and Smoothing architecture, as well as an external synchronization
 *          function. These classes act as an interface only.
 * @author  Stephen Williams
 */

// \callgraph
#pragma once

#include <gtsam/nonlinear/NonlinearFactorGraph.h>

namespace gtsam {

// Forward declare the Filter and Smoother classes for the 'synchronize' function
class ConcurrentFilter;
class ConcurrentSmoother;

void synchronize(ConcurrentFilter& filter, ConcurrentSmoother& smoother);

/**
 * The interface for the 'Filter' portion of the Concurrent Filtering and Smoother architecture.
 */
class ConcurrentFilter {

protected:

  friend void synchronize(ConcurrentFilter& filter, ConcurrentSmoother& smoother);

  /** Default constructor */
  ConcurrentFilter() {};

  /** Default destructor */
  virtual ~ConcurrentFilter() {};

  /**
   * Perform any required operations before the synchronization process starts.
   * Called by 'synchronize'
   */
  virtual void presync() {};

  /**
   * Populate the provided containers with factors that constitute the filter branch summarization
   * needed by the smoother. Also, linearization points for the new root clique must be provided.
   *
   * @param summarizedFactors The summarized factors for the filter branch
   * @param rootValues The linearization points of the root clique variables
   */
  virtual void getSummarizedFactors(NonlinearFactorGraph& summarizedFactors, Values& rootValues) = 0;

  /**
   * Populate the provided containers with factors being sent to the smoother from the filter. These
   * may be original nonlinear factors, or factors encoding a summarization of the filter information.
   * The specifics will be implementation-specific for a given filter.
   *
   * @param smootherFactors The new factors to be added to the smoother
   * @param smootherValues The linearization points of any new variables
   */
  virtual void getSmootherFactors(NonlinearFactorGraph& smootherFactors, Values& smootherValues) = 0;

  /**
   * Apply the updated version of the smoother branch summarized factors.
   *
   * @param summarizedFactors An updated version of the smoother branch summarized factors
   */
  virtual void synchronize(const NonlinearFactorGraph& summarizedFactors) = 0;

  /**
   * Perform any required operations after the synchronization process finishes.
   * Called by 'synchronize'
   */
  virtual void postsync() {};

}; // ConcurrentFilter

/**
 * The interface for the 'Smoother' portion of the Concurrent Filtering and Smoother architecture.
 */
class ConcurrentSmoother {

protected:

  friend void synchronize(ConcurrentFilter& filter, ConcurrentSmoother& smoother);

  /** Default constructor */
  ConcurrentSmoother() {};

  /** Default destructor */
  virtual ~ConcurrentSmoother() {};

  /**
   * Perform any required operations before the synchronization process starts.
   * Called by 'synchronize'
   */
  virtual void presync() {};

  /**
   * Populate the provided containers with factors that constitute the smoother branch summarization
   * needed by the filter.
   *
   * @param summarizedFactors The summarized factors for the filter branch
   */
  virtual void getSummarizedFactors(NonlinearFactorGraph& summarizedFactors) = 0;

  /**
   * Apply the new smoother factors sent by the filter, and the updated version of the filter
   * branch summarized factors.
   *
   * @param smootherFactors A set of new factors added to the smoother from the filter
   * @param smootherValues Linearization points for any new variables
   * @param summarizedFactors An updated version of the filter branch summarized factors
   * @param rootValues The linearization point of the root variables
   */
  virtual void synchronize(const NonlinearFactorGraph& smootherFactors, const Values& smootherValues,
      const NonlinearFactorGraph& summarizedFactors, const Values& rootValues) = 0;

  /**
   * Perform any required operations after the synchronization process finishes.
   * Called by 'synchronize'
   */
  virtual void postsync() {};

}; // ConcurrentSmoother

}/// namespace gtsam
