#include <cstdio>

#include <rmq.h>

using baron::RMQ;

int main(int argc, char **argv) {

	RMQ::Array a{ 1, 5, 4, -1, 3, 2, 0, 6, 3, 4 };

	RMQ rmq{ a };
	rmq.makeIndex();

	int i = 4, j = 7;
	printf("RMQ(%d, %d) = %d", i, j, rmq.query(i, j));

	return 0;
}