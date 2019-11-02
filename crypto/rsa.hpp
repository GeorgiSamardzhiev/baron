#ifndef RSA_HPP
#define RSA_HPP

#include <vector>

namespace baron {

	long long moduloInverse(long long a, long long n);
	bool isLegalExponent(long long e, long long p, long long q);
	long long generatePrivateExponent(long long e, long long p, long long q);
	std::vector<long long> encrypt(std::vector<long long>& payload, long long e, long long n);
	std::vector<long long> decrypt(std::vector<long long>& payload, long long d, long long n);

}

#endif // !RSA_HPP
