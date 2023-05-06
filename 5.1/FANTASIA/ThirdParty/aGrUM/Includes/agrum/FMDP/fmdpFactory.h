
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
 * @brief Headers of the FMDPFactory class.
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 */

#ifndef GUM_FMDP_FACTORY_H
#define GUM_FMDP_FACTORY_H
//======================================================================
#include <string>
#include <vector>
//======================================================================
#include <agrum/core/sequence.h>

#include <agrum/variables/labelizedVariable.h>

#include <agrum/FMDP/IfmdpFactory.h>
#include <agrum/FMDP/fmdp.h>


namespace gum {

  /**
   * @class FMDPFactory
   * @headerfile fmdpFactory.h <agrum/FMDP/fmdpFactory.h>
   * @brief A factory class to ease Factored Markov Decision Process
   * construction.
   * @ingroup fmdp_group
   *
   * A FMDPFactory will never create a Factored Markov Decision Process and
   * works on only one
   * Factored Markov Decision Process.
   *
   * The only exception of this behaviour is when you create a copy of the
   * factory,
   * it will create a copy of its FMDP. This is useful when you want to create
   * two FMDP sharing a common base.
   * However be very careful because the copy will not delete its FMDP.
   *
   * Each method will raise an OperationNotAllowed if you call it when the
   * factory
   * is not in a valid state for that call. The error message is "Illegal
   * state.".
   *
   */

  template < typename GUM_SCALAR >
  class FMDPFactory : public AbstractFMDPFactory {
    public:
    // ==========================================================================
    /// @name Constructor & destructor.
    // ==========================================================================
    /// @{

    /**
     * Use this constructor if you want to use an already created factored
     * markov decision process.
     * @param fmdp A pointer over the @ref FMDP filled by this factory.
     */
    FMDPFactory(FMDP< GUM_SCALAR >* fmdp);

    /**
     * @brief Destructor.
     *
     * To prevent strange behaviour you should always destroy a FMDPFactory
     * when it's state equals NONE.
     *
     * @throw FatalError Raised if the state of the factory prevents it to die
     *                   peacefully.
     */
    ~FMDPFactory();

    /// @}
    // ==========================================================================
    /// @name Getter and setters.
    // ==========================================================================
    /// @{

    /**
     * Returns the Factored Markov Decision Process created by this factory.
     * @throw OperationNotAllowed Raise if the state of the factory is different
     *                            than NONE.
     */
    FMDP< GUM_SCALAR >* fmdp() const;

    /// Returns the current state of the factory.
    FMDPfactory_state state() const;

    /// Returns a constant reference on a variable given it's name.
    /// @throw NotFound Raised if no variable matches the name.
    const DiscreteVariable* variable(const std::string& name) const;

    /// @}
    // ==========================================================================
    /// @name Variable declaration methods (NONE -> VARIABLE)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in a variable declaration.
    void startVariableDeclaration();

    /// Tells the factory the current variable's name.
    /// @throw DuplicateElement Raised if a variable with the same name already
    ///                         exist.
    void variableName(const std::string& name);

    /// Tells the factory the current variable's description.
    void variableDescription(const std::string& desc);

    /// Adds a modality to the current variable.
    void addModality(const std::string& name);

    /// Tells the factory that we're out of a variable declaration.
    /// @throw UndefinedElement Raised if the variable isn't defined (or not
    ///                         enough defined).
    void endVariableDeclaration();

    /// @}
    // ==========================================================================
    /// @name Action declaration methods (NONE -> ACTION)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in an action declaration.
    void startActionDeclaration();

    /// Tells the factory to add an action to the current fmdp.
    void addAction(const std::string& action);

    /// Tells the factory that we're out of an action declaration.
    void endActionDeclaration();

    /// @}
    // ==========================================================================
    /// @name Transition declaration methods (NONE -> TRANSITION <- ACTION)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in a transition declaration.
    void startTransitionDeclaration();

    /// Tells the factory to add a transition table to the current fmdp.
    void addTransition(const std::string&        var,
                       const MultiDimAdressable* transition);

    /// Tells the factory to add a transition table to the current fmdp.
    /// This transition table will be extracted from incorporated
    /// multiDimFunctionGraph.
    void addTransition(const std::string& var);

    /// Tells the factory that we're out of a transition declaration.
    void endTransitionDeclaration();

    /// @}
    // ==========================================================================
    /// @name Cost declaration methods (NONE -> COST <- ACTION)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in a cost declaration.
    void startCostDeclaration();

    /// Tells the factory to add a cost table to the current fmdp.
    void addCost(const MultiDimAdressable* cost);

    /// Tells the factory to add a cost table to the current fmdp.
    /// This cost table will be extracted from incorporated
    /// multiDimFunctionGraph.
    void addCost();

    /// Tells the factory that we're out of a cost declaration.
    void endCostDeclaration();

    /// @}
    // ==========================================================================
    /// @name Reward declaration methods (NONE -> REWARD <- ACTION)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in a reward declaration.
    void startRewardDeclaration();

    /// Tells the factory that we're in a reward declaration mode where the
    /// global reward diagram is an operation between
    /// simplier decision diagram..
    void setOperationModeOn(std::string operationType);

    /// Tells the factory to add a reward table to the current fmdp.
    void addReward(const MultiDimAdressable* reward);

    /// Tells the factory to add a reward table to the current fmdp.
    /// This reward table will be extracted from incorporated
    /// multiDimFunctionGraph.
    void addReward();

    /// Tells the factory that we're out of a cost declaration.
    void endRewardDeclaration();

    /// @}
    // ==========================================================================
    /// @name Discount declaration methods (NONE -> DISCOUNT)
    // ==========================================================================
    /// @{

    /// Tells the factory that we're in a cost declaration.
    void startDiscountDeclaration();

    /// Tells the factory to add a cost table to the current fmdp.
    void addDiscount(float discount);

    /// Tells the factory that we're out of a cost declaration.
    void endDiscountDeclaration();

    /// @}
    // ==========================================================================
    /// @name FunctionGraph Creation specific methods
    /// @brief methods used by internal FunctionGraphfactory to build up
    /// a multidimFunctionGraph
    // ==========================================================================
    /// @{

    /// Insert in diagram a non terminal node
    NodeId addInternalNode(std::string name_of_var);

    /// Insert in diagram a terminal node
    NodeId addTerminalNode(float value);

    ///
    void addArc(NodeId from, NodeId to, Idx modality);

    /// add an arc in diagram
    void setRoot(NodeId rootId);

    /// @}

    private:
    // ==========================================================================
    /// @name Current constructed FMDP's parts.
    // ==========================================================================
    /// @{

    /// Depending on the context this flag is used for some VERY important
    /// reasons.
    bool __foo_flag;

    /// Depending on the context this flag is used for some VERY important
    /// reasons.
    bool __bar_flag;

    /// Just to keep track of strings between two start/end calls.
    std::vector< std::string > __stringBag;

    /// Just to keep track of multidim between two start/end calls.
    std::vector< const MultiDimImplementation< GUM_SCALAR >* > __ddBag;

    /// Used in VARIABLE mode
    /// Checks if in __stringBag there is no other modality with the same name.
    void __checkModalityInBag(const std::string& mod);

    /// Reset the different parts used to constructed the FMDP.
    void __resetParts();

    /// Insert every variables in the function graph
    void __initializeFunctionGraph();

    /// Insert every variables in the function graph
    void __finalizeFunctionGraph();

    /// @}

    /// State stack.
    std::vector< FMDPfactory_state > __states;

    /// The constructed FMDP
    FMDP< GUM_SCALAR >* __fmdp;

    /// The FunctionGraph we're building at a given time
    MultiDimFunctionGraph< GUM_SCALAR >* __FunctionGraph;

    /// Mapping between a declared variable's name and itself.
    HashTable< std::string, const DiscreteVariable* > __varNameMap;

    /// Action Id counter
    Idx __actionIdcpt;

    /// Copy operator is illegal, use only copy constructor.
    FMDPFactory< GUM_SCALAR >& operator=(const FMDPFactory< GUM_SCALAR >& source);

    /// Raise an OperationNotAllowed with the message "Illegal state."
    void __illegalStateError(const std::string& s);
  };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
  extern template class FMDPFactory< double >;
#endif

} /* namespace gum */


#include <agrum/FMDP/fmdpFactory_tpl.h>

#endif   // GUM_FMDP_FACTORY_H