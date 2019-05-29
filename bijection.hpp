#ifndef BIJECTION_HPP
#define BIJECTION_HPP

namespace baron {

	//bijective f:NxN->N
	unsigned long long naturalPairBijection(unsigned long long x, unsigned long long y);

	//bijective f:N->Z
	long long naturalToIntegerBijection(unsigned long long x);

	//bijective f:Z->N
	unsigned long long integerToNaturalBijection(long long y);

	//bijective f:ZxZ->N
	unsigned long long IntegerPairToNaturalBijection(long long x, long long y);

	//bijective f:ZxZ->N
	long long IntegerPairToIntegerlBijection(long long x, long long y);

}

#endif // !BIJECTION_HPP
