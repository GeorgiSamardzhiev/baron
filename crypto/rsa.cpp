
#include "rsa.hpp"
#include "../math/gcd.hpp"
#include "../math/arithmetic.hpp"

namespace baron {

	long long moduloInverse(long long a, long long n) {
		return extendedGCD(a, n).first % n;
	}

	bool isLegalExponent(long long e, long long p, long long q) {
		long long n = (p-1)*(q-1);
		return (e > 1) && (e < n) && (gcd(e, n) == 1);
	}

	long long generatePrivateExponent(long long e, long long p, long long q) {
		if (isLegalExponent(e, p, q)) {
			long long n = (p-1)*(q-1);
			return moduloInverse(e, n);
		}
		throw "Not a legal public exponent";
	}

	std::vector<long long> encrypt(std::vector<long long>& payload, long long e, long long n) {
		std::vector<long long> res;
		size_t size = payload.size();
		for (size_t j = 0; j < size; j++) {
			if (payload[j]>n) {
				throw "Encryption error! Modulus is too small.";
			}
			res.push_back(modPower(payload[j], e, n));
		}
		return res;
	}

	std::vector<long long> decrypt(std::vector<long long>& payload, long long d, long long n) {
		std::vector<long long> res;
		size_t size = payload.size();
		for (size_t j = 0; j < size; j++) {
			if (payload[j]>n) {
				throw "Decryption error! Modulus is too small.";
			}
			res.push_back(modPower(payload[j], d, n));
		}
		return res;
	}

}