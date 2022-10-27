
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


/** @file
 * @brief Source implementation of InfluenceDiagramGenerator
 *
 * @author Jean-Christophe MAGNAN and Pierre-Henri WUILLEMIN
 *
 */
#include <agrum/ID/generator/influenceDiagramGenerator.h>

namespace gum {

  // Default constructor.
  // Use the SimpleCPTGenerator for generating the IDs CPT.
  template < typename GUM_SCALAR >
  InfluenceDiagramGenerator< GUM_SCALAR >::InfluenceDiagramGenerator() {
    GUM_CONSTRUCTOR(InfluenceDiagramGenerator);
    __cptGenerator = new SimpleCPTGenerator< GUM_SCALAR >();
    __utGenerator = new SimpleUTGenerator();
  }

  // Use this constructor if you want to use a different policy for generating
  // CPT than the default one.
  // The cptGenerator will be erased when the destructor is called.
  // @param cptGenerator The policy used to generate CPT.
  template < typename GUM_SCALAR >
  InfluenceDiagramGenerator< GUM_SCALAR >::InfluenceDiagramGenerator(
     ICPTGenerator< GUM_SCALAR >* cptGenerator) {
    GUM_CONSTRUCTOR(InfluenceDiagramGenerator);
    __cptGenerator = cptGenerator;
    __utGenerator = new SimpleUTGenerator();
  }

  // Use this constructor if you want to use a different policy for generating
  // UT than the default one.
  // The utGenerator will be erased when the destructor is called.
  // @param utGenerator The policy used to generate UT.
  template < typename GUM_SCALAR >
  InfluenceDiagramGenerator< GUM_SCALAR >::InfluenceDiagramGenerator(
     UTGenerator* utGenerator) {
    GUM_CONSTRUCTOR(InfluenceDiagramGenerator);
    __cptGenerator = new SimpleCPTGenerator< GUM_SCALAR >();
    __utGenerator = utGenerator;
  }

  // Use this constructor if you want to use a different policy for generating
  // both CPT & UT than the defaults ones.
  // The cptGenerator and utGenerator will be erased when the destructor is
  // called.
  // @param cptGenerator The policy used to generate CPT.
  // @param utGenerator The policy used to generate UT.
  template < typename GUM_SCALAR >
  InfluenceDiagramGenerator< GUM_SCALAR >::InfluenceDiagramGenerator(
     ICPTGenerator< GUM_SCALAR >* cptGenerator, UTGenerator* utGenerator) {
    GUM_CONSTRUCTOR(InfluenceDiagramGenerator);
    __cptGenerator = cptGenerator;
    __utGenerator = utGenerator;
  }

  // Destructor.
  template < typename GUM_SCALAR >
  InfluenceDiagramGenerator< GUM_SCALAR >::~InfluenceDiagramGenerator() {
    GUM_DESTRUCTOR(InfluenceDiagramGenerator);
    delete __cptGenerator;
    delete __utGenerator;
  }

  // Generates an influence diagram using floats.
  // @param nbrNodes The number of nodes in the generated ID.
  // @param arcdensity The probability of adding an arc between two nodes.
  // @param chanceNodeDensity The proportion of chance node
  // @param utilityNodeDensity The proportion of utility node
  // @param max_modality Each DRV has from 2 to max_modality modalities
  // @return A IDs randomly generated.
  template < typename GUM_SCALAR >
  InfluenceDiagram< GUM_SCALAR >*
     InfluenceDiagramGenerator< GUM_SCALAR >::generateID(
        Size       nbrNodes,
        GUM_SCALAR arcDensity,
        GUM_SCALAR chanceNodeDensity,
        GUM_SCALAR utilityNodeDensity,
        Size       max_modality) {
    InfluenceDiagram< GUM_SCALAR >* influenceDiagram =
       new InfluenceDiagram< GUM_SCALAR >();
    // First we add nodes
    HashTable< Size, NodeId > map;
    std::stringstream         strBuff;
    Size                      nb_mod;

    for (Idx i = 0; i < nbrNodes; ++i) {
      strBuff << i;
      nb_mod = (max_modality == 2) ? 2 : 2 + rand() % (max_modality - 1);

      GUM_SCALAR cnd = chanceNodeDensity * (GUM_SCALAR)RAND_MAX;
      GUM_SCALAR und = utilityNodeDensity * (GUM_SCALAR)RAND_MAX;

      GUM_SCALAR d = (GUM_SCALAR)rand();

      if (d < cnd)
        map.insert(i,
                   influenceDiagram->addChanceNode(
                      LabelizedVariable(strBuff.str(), "", nb_mod)));
      else if (d < (cnd + und))
        map.insert(i,
                   influenceDiagram->addUtilityNode(
                      LabelizedVariable(strBuff.str(), "", 1)));
      else
        map.insert(i,
                   influenceDiagram->addDecisionNode(
                      LabelizedVariable(strBuff.str(), "", nb_mod)));

      strBuff.str("");
    }

    // We add arcs
    GUM_SCALAR p = arcDensity * (GUM_SCALAR)RAND_MAX;

    for (Size i = 0; i < nbrNodes; ++i)
      if (!influenceDiagram->isUtilityNode(map[i]))
        for (Size j = i + 1; j < nbrNodes; ++j)
          if (((GUM_SCALAR)rand()) < p) {
            influenceDiagram->addArc(map[i], map[j]);
          }

    // And fill the CPTs and UTs
    for (Size i = 0; i < nbrNodes; ++i)
      if (influenceDiagram->isChanceNode(map[i]))
        __cptGenerator->generateCPT(
           influenceDiagram->cpt(map[i]).pos(influenceDiagram->variable(map[i])),
           influenceDiagram->cpt(map[i]));
      else if (influenceDiagram->isUtilityNode(map[i]))
        __utGenerator->generateUT(influenceDiagram->utility(map[i]).pos(
                                     influenceDiagram->variable(map[i])),
                                  influenceDiagram->utility(map[i]));

    __checkTemporalOrder(influenceDiagram);

    return influenceDiagram;
  }

  template < typename GUM_SCALAR >
  void InfluenceDiagramGenerator< GUM_SCALAR >::__checkTemporalOrder(
     InfluenceDiagram< GUM_SCALAR >* infdiag) {
    if (!infdiag->decisionOrderExists()) {
      Sequence< NodeId > order = infdiag->topologicalOrder(true);

      auto orderIter = order.begin();

      while ((orderIter != order.end()) && (!infdiag->isDecisionNode(*orderIter)))
        ++orderIter;

      if (orderIter == order.end()) return;

      NodeId parentDecision = (*orderIter);

      ++orderIter;

      for (; orderIter != order.end(); ++orderIter)
        if (infdiag->isDecisionNode(*orderIter)) {
          infdiag->addArc(parentDecision, (*orderIter));
          parentDecision = (*orderIter);
        }
    }
  }

} /* namespace gum */