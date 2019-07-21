#ifndef BIJECTION_HPP
#define BIJECTION_HPP

#include <utility>

namespace baron {

	//bijective f:NxN->N
	unsigned long long naturalPairToNaturalBijection(unsigned long long x, unsigned long long y);

	//bijective f:N->NxN
	std::pair<unsigned long long, unsigned long long> naturalToNaturalPairBijection(unsigned long long x);

	//bijective f:N->Z
	long long naturalToIntegerBijection(unsigned long long x);

	//bijective f:Z->N
	unsigned long long integerToNaturalBijection(long long y);

	//bijective f:ZxZ->N
	unsigned long long integerPairToNaturalBijection(long long x, long long y);

	//bijective f:ZxZ->N
	long long integerPairToIntegerlBijection(long long x, long long y);

}

#endif // !BIJECTION_HPP
