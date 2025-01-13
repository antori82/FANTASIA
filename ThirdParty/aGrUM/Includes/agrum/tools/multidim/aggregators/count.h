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
 * @brief count aggregator
 *
 * @author Pierre-Henri WUILLEMIN(_at_LIP6) & Christophe GONZALES(_at_AMU)
 */

#ifndef GUM_COUNT_AGGREGATOR_H
#define GUM_COUNT_AGGREGATOR_H

#include <agrum/tools/multidim/aggregators/multiDimAggregator.h>

namespace gum {

  namespace aggregator {
    // =========================================================================
    // ===                     GUM_MAX_AGGREGATOR                            ===
    // =========================================================================

    /**
     * @class Count
     * @headerfile count.h <agrum/tools/multidim/aggregators/count.h>
     * @ingroup multidim_agg_group
     *
     * @brief count aggregator
     *
     * @see MultiDimAggregator for more details of implementations
     *
     * Note that a <tt>Count(i)</tt> aggregator with a binary aggregator
     * variable is the \f$ \exists i \f$ aggregator.  If the aggregator
     * variable is n-ary variable, <tt>Count(i)</tt> can serve as the \f$
     * \exists \f$ at least \f$ n\ times\ i \f$ aggregator.
     */
    template < typename GUM_SCALAR >
    class Count: public MultiDimAggregator< GUM_SCALAR > {
      public:
      Count(Idx value);
      Count(const Count< GUM_SCALAR >& from);
      virtual ~Count();

      virtual std::string aggregatorName() const;

      /**
       * This method creates a clone of this object, withouth its content
       * (including variable), you must use this method if you want to ensure
       * that the generated object has the same type than the object containing
       * the called newFactory()
       *
       * For example :
       * @code
       *   MultiDimArray<double> y;
       *   MultiDimContainer<double>* x = y.newFactory();
       * @endcode
       *
       * Then x is a MultiDimArray<double>*
       *
       * @warning you must desallocate by yourself the memory
       * @return an empty clone of this object with the same type
       */
      virtual MultiDimContainer< GUM_SCALAR >* newFactory() const;

      protected:
      virtual Idx neutralElt_() const;
      virtual Idx fold_(const DiscreteVariable& v, Idx i1, Idx i2, bool& stop_iteration) const;

      private:
      Idx _value_;
    };


#ifndef GUM_NO_EXTERN_TEMPLATE_CLASS
    extern template class Count< double >;
#endif


  }   // namespace aggregator
}   // namespace gum

#include <agrum/tools/multidim/aggregators/count_tpl.h>

#endif   // GUM_COUNT_AGGREGATOR_H
