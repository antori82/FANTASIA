
/**
 *
 *  Copyright 2005-2019 Pierre-Henri WUILLEMIN et Christophe GONZALES (LIP6)
 *   {prenom.nom}_at_lip6.fr
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


/**
 * @file
 * @brief Headers of the States Counter class.
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */

// =========================================================================
#ifndef GUM_STATES_COUNTER_H
#define GUM_STATES_COUNTER_H
// =========================================================================
#include <agrum/core/sequence.h>
// =========================================================================
#include <agrum/FMDP/learning/datastructure/IVisitableGraphLearner.h>
// =========================================================================
#include <agrum/multidim/implementations/multiDimFunctionGraph.h>
// =========================================================================

namespace gum {


  /**
   * @class StatesCounter statesCounter.h
   * <agrum/FMDP/simulation/statesCounter.h>
   * @brief Provides the necessary to check whether or not states have been
   * already visited.
   * @ingroup fmdp_group
   */
  class StatesCounter : public IVisitableGraphLearner {
    public:
    // ==========================================================================
    /// @name Constructor & destructor.
    // ==========================================================================
    /// @{

    /**
     * Default constructor
     */
    StatesCounter();

    /**
     * Default destructor
     */
    ~StatesCounter();

    /// @}

    // ==========================================================================
    /// @name Miscelleanous methods
    // ==========================================================================
    /// @{

    void incState(const Instantiation&);

    void reset(const Instantiation&);

    const MultiDimFunctionGraph< int >* counter();

    /// @}


    // ###################################################################
    /// @name Visit Methods
    // ###################################################################
    /// @{
    public:
    // ==========================================================================
    ///
    // ==========================================================================
    NodeId root() const { return __counter->root(); }

    // ==========================================================================
    ///
    // ==========================================================================
    bool isTerminal(NodeId ni) const { return __counter->isTerminalNode(ni); }

    // ==========================================================================
    ///
    // ==========================================================================
    const DiscreteVariable* nodeVar(NodeId ni) const {
      return __counter->node(ni)->nodeVar();
    }

    // ==========================================================================
    ///
    // ==========================================================================
    NodeId nodeSon(NodeId ni, Idx modality) const {
      return __counter->node(ni)->son(modality);
    }

    // ==========================================================================
    ///
    // ==========================================================================
    Idx nodeNbObservation(NodeId ni) const { return __counter->nodeValue(ni); }

    void insertSetOfVars(MultiDimFunctionGraph< double >* ret) const {
      for (SequenceIteratorSafe< const DiscreteVariable* > varIter =
              __counter->variablesSequence().beginSafe();
           varIter != __counter->variablesSequence().endSafe();
           ++varIter)
        ret->add(**varIter);
    }


    /// @}

    private:
    void __incState(const Instantiation&, NodeId, Idx, Size);

    MultiDimFunctionGraph< Size >* __counter;

    Set< Instantiation* > __visitedStates;
  };
} /* namespace gum */

#endif   // GUM_STATES_COUNTER_H