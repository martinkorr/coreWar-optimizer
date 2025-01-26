/* ----------------------------------------------------------------------------
  mbwall 25feb95
  Copyright (c) 1995 Massachusetts Institute of Technology
                     all rights reserved
---------------------------------------------------------------------------- */

#pragma once

#include <GAAllele.h>
#include <GA1DArrayGenome.hpp>

using GARealAlleleSet = GAAlleleSet<float>;
using GARealAlleleSetArray = GAAlleleSetArray<float>;

using GARealGenome = GA1DArrayAlleleGenome<float>;

int GARealGaussianMutator(GAGenome &, float);

// in one (and only one) place in the code that uses the string genome, you 
// should define INSTANTIATE_STRING_GENOME in order to force the specialization
// for this genome.
#if defined(INSTANTIATE_REAL_GENOME)
#include <GARealGenome.C>
#endif

inline void GARealUniformInitializer(GAGenome& g){
  GA1DArrayAlleleGenome<float>::UniformInitializer(g);
}
inline void GARealOrderedInitializer(GAGenome& g){
  GA1DArrayAlleleGenome<float>::OrderedInitializer(g);
}

inline int GARealUniformMutator(GAGenome& g, float pmut){
  return GA1DArrayAlleleGenome<float>::FlipMutator(g, pmut);
}
inline int GARealSwapMutator(GAGenome& g, float pmut){
  return GA1DArrayGenome<float>::SwapMutator(g, pmut);
}


inline int GARealUniformCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::UniformCrossover(a,b,c,d);
}
inline int GARealEvenOddCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::EvenOddCrossover(a,b,c,d);
}
inline int GARealOnePointCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::OnePointCrossover(a,b,c,d);
}
inline int GARealTwoPointCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::TwoPointCrossover(a,b,c,d);
}
inline int GARealPartialMatchCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::PartialMatchCrossover(a,b,c,d);
}
inline int GARealOrderCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::OrderCrossover(a,b,c,d);
}
inline int GARealCycleCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d) {
  return GA1DArrayGenome<float>::CycleCrossover(a,b,c,d);
}
int GARealArithmeticCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d);
int GARealBlendCrossover(const GAGenome& a, const GAGenome& b,
				  GAGenome* c, GAGenome* d);
