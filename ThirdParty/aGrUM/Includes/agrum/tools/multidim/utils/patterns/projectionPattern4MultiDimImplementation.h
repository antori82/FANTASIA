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


/**
 * @file
 *
 * @brief the pattern used by all the MultiDimImplementation projections
 *
 * @author Christophe GONZALES(_at_AMU) and Pierre-Henri WUILLEMIN(_at_LIP6)
 */

// check if we allowed these patterns to be used
#ifndef GUM_PROJECTION_PATTERN_ALLOWED

// #warning To use projectionPattern4MultiDimImplementation.h, you must define
// GUM_PROJECTION_PATTERN_ALLOWED

#else

namespace gum {

#  ifdef GUM_MULTI_DIM_PROJECTION_NAME
  template < typename GUM_SCALAR >
  MultiDimImplementation< GUM_SCALAR >*
     GUM_MULTI_DIM_PROJECTION_NAME(const MultiDimImplementation< GUM_SCALAR >& ttable,
                                   const Set< const DiscreteVariable* >&       del_vars) {
#  endif

    typename ProjectionRegister4MultiDim< GUM_SCALAR >::ProjectionPtr func;

    // get the appropriate function to perform the operation
    try {
      // try to find func(ttable,del_vars) in the register
      func = ProjectionRegister4MultiDim< GUM_SCALAR >::Register().get(
         GUM_MULTI_DIM_PROJECTION_FUNC_NAME,
         ttable.name());
    } catch (NotFound const&) {
      func = ProjectionRegister4MultiDim< GUM_SCALAR >::Register().get(
         GUM_MULTI_DIM_PROJECTION_FUNC_NAME,
         ttable.basename());
    }

    // perform the projection
    return func(&ttable, del_vars);
  }
}   // namespace gum
#endif /* GUM_PROJECTION_PATTERN_ALLOWED */
