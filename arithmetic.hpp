#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

namespace baron {

	template <typename T, typename H>
	T modPower(T x, H p, H m) {
		T res = 1;
		x %= m;
		while (p > 0) {
			if (p & 1) { //  if p is odd
				res = (res*x) % m;
			}
			p >>= 1;
			x = (x*x) % m;
		}
		return res;
	}

}
#endif // !ARITHMETIC_HPP
