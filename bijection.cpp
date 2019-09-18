#include "bijection.hpp"
#include <cmath>

namespace baron {

	unsigned long long naturalPairToNaturalBijection(unsigned long long x, unsigned long long y) {
		return pow(2, x)*((y<<1) + 1) - 1;
	}

	std::pair<unsigned long long, unsigned long long> naturalToNaturalPairBijection(unsigned long long z) {
		long long x = 0;
		long long zCopy = z+1;
		while (zCopy != 0 && zCopy%2 == 0) {
			++x;
			zCopy >>= 1;
		}
		long long y = ((long long)((z+1)/pow(2, x)) - 1)>>1;
		return std::make_pair(x, y);
	}

	long long naturalToIntegerBijection(unsigned long long x) {
		if (x&1) {
			return -(long long)x>>1;
		}
		return x>>1;
	}

	unsigned long long integerToNaturalBijection(long long y) {
		if (y>=0) {
			return y<<1;
		}
		return -(y<<1) - 1;
	}

	unsigned long long integerPairToNaturalBijection(long long x, long long y) {
		return naturalPairToNaturalBijection(integerToNaturalBijection(x), integerToNaturalBijection(y));
	}

	long long integerPairToIntegerlBijection(long long x, long long y) {
		return naturalToIntegerBijection(integerPairToNaturalBijection(x, y));
	}

}
