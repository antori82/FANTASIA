/**
 *
 *   Copyright (c) 2005-2023  by Pierre-Henri WUILLEMIN(_at_LIP6) et Christophe GONZALES(_at_AMU)
 * (_at_AMU) info_at_agrum_dot_org
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
 * @brief Class representing Markov network (legacy : PLEASE USE MarkovRandomField)
 *
 * @author Pierre-Henri WUILLEMIN(_at_LIP6) & Christophe GONZALES(_at_AMU)
 *
 */
#ifndef GUM_MARKOV_NET_H
#define GUM_MARKOV_NET_H

#include "agrum/MRF/MarkovRandomField.h"

namespace gum {
  template < typename GUM_SCALAR >
  using MarkovNet [[deprecated("Class MarkovNet<GUM_SCALAR> is deprecated. Please use class "
                               "MarkovRandomField<GUM_SCALAR> instead.")]]
  = MarkovRandomField< GUM_SCALAR >;
}   // namespace gum
#endif /* GUM_MARKOV_NET_H */
