#include <cstdio>

#include "rmq.hpp"

using baron::RMQ;

int main(int argc, char **argv) {

	bool useNaive = false;
	if (argc > 1) {
		--argc;
		while (argc-- > 0) {
			if (!strncmp(argv[argc], "use-naive", strlen(argv[argc]))) {
				useNaive = true;
			}
		}
	}

	RMQ::Array a{ 1, 5, 4, -1, 3, 2, 0, 6, 3, 4 };

	RMQ rmq{ a, useNaive };
	rmq.makeIndex();

	int i = 4, j = 7;
	printf("RMQ(%d, %d) = %d", i, j, rmq.query(i, j));

	int g = 0;
	scanf_s("%d", &g);

	return 0;
}