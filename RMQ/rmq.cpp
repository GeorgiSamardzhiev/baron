#include <rmq.h>

// C includes
#include <cassert>

// C++ includes
#include <algorithm>

using baron::RMQ;

RMQ::RMQ(const Array &array) : array(array), flags(0) {
	setFlag(use_naive);
	setFlag(array_initialized);
}

void baron::RMQ::setArray(const Array &array) {
	clearFlags();

	this->array = array;
	setFlag(array_initialized);
	if (!array.empty()) setFlag(array_not_empty);
}

void RMQ::makeIndex() {
	assert(checkFlag(array_initialized | array_not_empty));

	if (checkFlag(use_naive)) {
		rmqIndexNaive();
	} else {
		rmqLog();
	}

	setFlag(index_made);
}

int RMQ::query(int start, int end) const {
	assert(checkFlag(index_made) && start >= 0 && end >= start && (Array::size_type)end < array.size());

	if (checkFlag(use_naive)) {
		return index[start][end];
	} else {
		return 0;
	}
}

void baron::RMQ::rmqIndexNaive() {
	if (checkFlag(index_made)) {
		return;
	}

	index.resize(array.size());
	std::for_each(index.begin(), index.end(), [this](Array &a) { a.resize(array.size()); });

	for (Array::size_type i = 0; i < array.size(); ++i) {
		int m = array[i];
		int idx = i;
		
		for (Array::size_type j = i; j < array.size(); ++j) {
			if (array[j] < m) {
				m = array[j];
				idx = j;
			}
			index[i][j] = idx;
		}
	}
}

void baron::RMQ::rmqLog() {

}

void baron::RMQ::clearFlags() {
	flags = 0;
}

void baron::RMQ::setFlag(RMQFlag flag) {
	flags |= flag;
}

void baron::RMQ::removeFlag(RMQFlag flag) {
	flags &= (~flag);
}

bool baron::RMQ::checkFlag(int flag) const {
	return flags & flag;
}
