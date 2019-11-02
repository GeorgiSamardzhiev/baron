#ifndef GCD_HPP
#define GCD_HPP

#include <utility>
#include <stdlib.h>

namespace baron {

	template <typename T>
	T gcd(const T& a, const T& b) {
		if (b==0) {
			return a;
		}
		return gcd(b, a%b);
	}

	//-- extendedGcd(a,b) = (x,y), such that a*x + b*y = gcd(a,b)
	template <typename T>
	std::pair<T, T> extendedGCD(const T& a, const T& b) {
		if (b == 0) {
			return std::make_pair(1, 0);
		}
		lldiv_t divMod = div(a, b);
		std::pair<T, T> pair = extendedGCD(b, divMod.rem);
		return std::make_pair(pair.second, pair.first - divMod.quot*pair.second);
	}

}
#endif // !GCD_HPP
