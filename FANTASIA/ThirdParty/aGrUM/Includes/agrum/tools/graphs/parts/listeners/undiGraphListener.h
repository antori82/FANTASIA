/**
 *
 *   Copyright (c) 2005-2023  by Pierre-Henri WUILLEMIN(_at_LIP6) & Christophe GONZALES(_at_AMU)
 *   info_at_agrum_dot_org
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


/** @file
 * @brief Base classes for undirected graph listeners
 *
 * @author Pierre-Henri WUILLEMIN(_at_LIP6)
 */
#ifndef GUM_UNDIGRAPH_LISTENER_H
#define GUM_UNDIGRAPH_LISTENER_H

#include <agrum/tools/graphs/undiGraph.h>

namespace gum {
  /** @class UndiGraphListener
   * @brief Abstract Base class for all undiGraph Listener
   *
   * \ingroup graph_group
   *
   *
   * This is the virtual base class for not-oriented graphs meta-listener.
   *
   * An UndiGraphListener will have to implement following pure methods :
   *  - void whenNodeAdded( const void * ,gum::NodeId )
   *  - void whenNodeDeleted( const void *,gum::NodeId )
   *  - void whenEdgeAdded( const void *,gum::NodeId,gum::NodeId )
   *  - void whenEdgeDeleted( const void *,gum::NodeId,gum::NodeId )
   */
  class UndiGraphListener: public Listener {
    public:
    // ############################################################################
    /// @name Constructors / Destructors
    // ############################################################################
    /// @{

    /// default constructor
    /** @param g the graph to listen to
     * @warning Note that, by the aGrUM's constructor parameter's rule, the fact
     * that g is passed as a pointer means that g is not copied, but only
     * referenced by the listener. */
    UndiGraphListener(UndiGraph* g);

    /// destructor
    ~UndiGraphListener();

    /// @}

    // ############################################################################
    /// @name signals to listen to
    // ############################################################################
    /// @{

    /// the action to take when a new node is inserted into the graph
    /** @param src the object that sent the signal
     * @param id the id of the new node inserted into the graph */
    virtual void whenNodeAdded(const void* src, NodeId id) = 0;

    /// the action to take when a node has just been removed from the graph
    /** @param src the object that sent the signal
     * @param id the id of the node has just been removed from the graph */
    virtual void whenNodeDeleted(const void* src, NodeId id) = 0;

    /// the action to take when a new edge is inserted into the graph
    /** @param src the object that sent the signal
     * @param id1 the id of one node of the edge inserted into the graph
     * @param id2 the id of the other node of the edge inserted into the graph
     */
    virtual void whenEdgeAdded(const void* src, NodeId id1, NodeId id2) = 0;

    /// the action to take when an edge has just been removed from the graph
    /** @param src the object that sent the signal
     * @param from the id of one node of the edge removed from the graph
     * @param to the id of the other node of the edge removed from the graph */
    virtual void whenEdgeDeleted(const void* src, NodeId from, NodeId to) = 0;

    /// @}

    protected:
    /// the graph to listen to
    UndiGraph* graph_;

    private:
    /// copy constructor (for the moment, this operation is forbidden)
    /** @param d the UndiGraphListener to copy */
    UndiGraphListener(const UndiGraphListener& d);

    /// copy operator (for the moment, this operation is forbidden)
    /** @param d the UndiGraphListener to copy */
    UndiGraphListener& operator=(const UndiGraphListener& d);
  };

}   // namespace gum

#ifndef GUM_NO_INLINE
#  include <agrum/tools/graphs/parts/listeners/undiGraphListener_inl.h>
#endif   // GUM_NOINLINE

#endif   // GUM_UNDIGRAPH_LISTENER_H
