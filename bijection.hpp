#ifndef BIJECTION_HPP
#define BIJECTION_HPP

#include <cmath>

namespace baron {

	//bijective f:NxN->N
	unsigned long long naturalPairBijection(unsigned long long x, unsigned long long y) {
		return pow(2, x)*(2*y + 1) - 1;
	}

	//bijective f:N->Z
	long long naturalToIntegerBijection(unsigned long long x) {
		if (x&1) {
			return (x+1)/2;
		}
		return x/2;
	}

	//bijective f:Z->N
	unsigned long long integerToNaturalBijection(long long y) {
		if (y>=0) {
			return 2*y;
		}
		return -2*y - 1;
	}

	//bijective f:ZxZ->N
	unsigned long long IntegerPairToNaturalBijection(long long x, long long y) {
		return naturalPairBijection(integerToNaturalBijection(x), integerToNaturalBijection(y));
	}

	//bijective f:ZxZ->N
	long long IntegerPairToIntegerlBijection(long long x, long long y) {
		return naturalToIntegerBijection(naturalPairBijection(integerToNaturalBijection(x), integerToNaturalBijection(y)));
	}

}

#endif // !BIJECTION_HPP
