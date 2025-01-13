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
 * @brief Headers of LayerGenerator.
 *
 * @author Lionel TORTI and Pierre-Henri WUILLEMIN(_at_LIP6)
 */

#ifndef GUM_LAYER_GENERATOR_H
#define GUM_LAYER_GENERATOR_H
#include <cstdlib>
#include <ctime>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <agrum/BN/generator/simpleBayesNetGenerator.h>

#include <agrum/PRM/PRMFactory.h>
#include <agrum/PRM/generator/PRMGenerator.h>

namespace gum {
  namespace prm {

    /**
     * @class LayerGenerator layerGenerator.h
     *<agrum/PRM/generator/layerGenerator.h>
     * @brief This class generates PRMs with a layer structure.
     *
     * @ingroup prm_group
     */
    template < typename GUM_SCALAR >
    class LayerGenerator: public PRMGenerator< GUM_SCALAR > {
      public:
      // ========================================================================
      /// @name Constructors and destructor.
      // ========================================================================
      /// @{

      /// Default constructor.
      LayerGenerator();
      /// Copy constructor.
      LayerGenerator(const LayerGenerator& source);
      /// Copy operator.
      LayerGenerator& operator=(const LayerGenerator& source);
      /// Destructor.
      virtual ~LayerGenerator();

      /// @}
      // ========================================================================
      /// Getters and setters.
      // ========================================================================
      /// @{

      /// Inner structure used to describe a Layer of the generated
      /// PRM<GUM_SCALAR>.
      struct LayerData {
        // Number of attributes for the layer's interface.
        Size a;
        // Number of aggregates for the layer's interface.
        Size g;
        // Number of classes for this layer.
        Size c;
        // Number of instances for this layer.
        Size o;
        // Density of arcs between attributes of the same classe in this layer.
        float inner_density;
        // The odds of an instance of the precedent layer to be added to a
        // reference slot of a class of this layer.
        float outter_density;
      };

      /// Returns the domain size of generated types.
      Size getDomainSize() const;

      /// Set the domain size of generated types.
      void setDomainSize(Size s);

      /// Returns the max number of parents allowed for any attribute or
      /// aggregator
      Size getMaxParents() const;

      /// Returns the max number of parents allowed for any attribute or
      /// aggregator
      void setMaxParents(Size s);

      /**
       * @brief Defines the structure of each layers.
       * Each value in v defines a layer, were v[i].first is the number of
       * different classes in the i-th layer and v[i].second is the number of
       * instances in the i-th layer.
       * @param v A vector describing each layer.
       */
      void setLayers(const std::vector< LayerData >& v);

      std::vector< LayerData >&       getLayer();
      const std::vector< LayerData >& getLayer() const;

      /// Proceeds with the generation of the PRM<GUM_SCALAR>.
      virtual PRM< GUM_SCALAR >* generate();

      /// @}
      private:
      std::vector< LayerData > _layers_;
      Size                     _domain_size_;
      Size                     _max_parents_;

      struct MyData {
        // interface name
        std::string                i;
        std::vector< std::string > a;
        std::vector< std::string > g;
        std::string                r;
        std::vector< std::string > c;
      };

      std::string _generateType_(PRMFactory< GUM_SCALAR >& f);

      void _generateInterfaces_(PRMFactory< GUM_SCALAR >& f,
                                const std::string&        type,
                                std::vector< MyData >&    l);

      void _generateClasses_(PRMFactory< GUM_SCALAR >&                       f,
                             const std::string&                              type,
                             std::vector< typename LayerGenerator::MyData >& l);

      void _generateClassDag_(Size                                            lvl,
                              DAG&                                            dag,
                              Bijection< std::string, NodeId >&               names,
                              std::vector< typename LayerGenerator::MyData >& l);

      void _generateSystem_(PRMFactory< GUM_SCALAR >&                       factory,
                            std::vector< typename LayerGenerator::MyData >& l);
    };

  } /* namespace prm */
} /* namespace gum */

#include <agrum/PRM/generator/layerGenerator_tpl.h>

#endif /* GUM_LAYER_GENERATOR_H */
