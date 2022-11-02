
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
 * @brief Headers of ClassDependencyGraph<GUM_SCALAR>.
 *
 * @author Lionel TORTI and Pierre-Henri WUILLEMIN
 */

#ifndef GUM_ClassDependencyGraph_H
#define GUM_ClassDependencyGraph_H

#include <agrum/PRM/PRM.h>

namespace gum {
  namespace prm {

    /**
     * @class ClassDependencyGraph
     * @headerfile classDependencyGraph.h <agrum/PRM/classDependencyGraph.h>
     * @brief This class represent the dependencies of all classes in a
     *PRM<GUM_SCALAR>.
     *
     * A Class Dependency Graph does listen to changes in it's PRM<GUM_SCALAR>.
     */
    template < typename GUM_SCALAR >
    class ClassDependencyGraph {
      public:
      /// Association between a class element and it's holding class.
      typedef std::pair< const PRMClassElementContainer< GUM_SCALAR >*,
                         const PRMClassElement< GUM_SCALAR >* >
         EltPair;

      // ========================================================================
      /// @name Constructors and Destructor.
      // ========================================================================
      /// @{

      /// Default constructor.
      /// @param prm The PRM<GUM_SCALAR> for which this
      /// ClassDependencyGraph<GUM_SCALAR> is constructed.
      ClassDependencyGraph(const PRM< GUM_SCALAR >& prm);

      /// Copy constructor.
      ClassDependencyGraph(const ClassDependencyGraph< GUM_SCALAR >& source);

      /// Destructor.
      ~ClassDependencyGraph();

      /// @}
      // ========================================================================
      /// @name Getters & setters.
      // ========================================================================
      /// @{

      /// Returns a constant reference over the graph of the DAG representing
      /// the ClassDependencyGraph<GUM_SCALAR>.
      const DAG& dag() const;

      /// Returns a constant reference over the element assiociated with the
      /// node
      /// id in the ClassDependencyGraph<GUM_SCALAR>.
      /// @throw NotFound Raised if no nodes matches id.
      const EltPair& get(NodeId id) const;

      /// @brief Returns the NodeId assign to the given
      /// PRMClassElement<GUM_SCALAR>
      /// of a
      ///        given Class.
      /// Is is necessary to give both Class and PRMClassElement<GUM_SCALAR>
      /// because
      /// inherited PRMClassElement<GUM_SCALAR> are shared in the inheritance
      /// hierarchy.
      NodeId get(const PRMClassElementContainer< GUM_SCALAR >& c,
                 const PRMClassElement< GUM_SCALAR >&          elt) const;

      /// Returns a mapping between the ClassDependencyGraph<GUM_SCALAR>'s nodes
      /// and
      /// their
      /// modalities.
      const NodeProperty< Size >& modalities() const;

      /// @}
      private:
      /// Build the class dependency graph.
      void __buildGraph(const PRM< GUM_SCALAR >& prm);

      /// Add nodes in __graph while updating consequently all the mappings.
      void __addNode(const PRMClassElementContainer< GUM_SCALAR >* c,
                     const PRMClassElement< GUM_SCALAR >&          elt);

      /// Add arcs in __graph.
      void
         __addArcs(const PRMClassElementContainer< GUM_SCALAR >&              c,
                   NodeId                                                     node,
                   HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >& map);

      /// The graph itself.
      DAG __graph;

      /// The modalities map for each node in the
      /// ClassDependencyGraph<GUM_SCALAR>.
      /// This
      /// is useful when using a Triangulation class over a
      /// ClassDependencyGraph<GUM_SCALAR>.
      NodeProperty< Size > __modalitites;

      /// Mapping between the nodes in __graph with the
      /// PRMClassElement<GUM_SCALAR>
      /// in
      /// the
      /// PRM<GUM_SCALAR>.
      NodeProperty< EltPair* > __elt_map;

      /// Code shortcut.
      typedef HashTable<
         const PRMClassElementContainer< GUM_SCALAR >*,
         HashTable< const PRMClassElement< GUM_SCALAR >*, NodeId >* >
         NodeMap;

      /// Map each Class to a HashTable mapping the Class's ClassElements to
      /// their
      /// assigned NodeId in __graph.
      NodeMap __node_map;
    };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
    extern template class ClassDependencyGraph< double >;
#endif

  } /* namespace prm */
} /* namespace gum */

#include <agrum/PRM/classDependencyGraph_tpl.h>

#endif /* GUM_ClassDependencyGraph_H */