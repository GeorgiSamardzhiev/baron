#include "sort.hpp"

namespace baron {

	void countingSort(int* arr, const int& size) {
		int max = 0;
		for (int i = 0; i<size; i++) {
			if (max < arr[i]) {
				max = arr[i];
			}
		}
		++max;
		int* help = new int[max];
		for (int i = 0; i<max; i++) {
			help[i] = 0;
		}
		for (int i = 0; i<size; i++) {
			++help[arr[i]];
		}
		for (int i = 0, j = 0; i<max; i++) {
			for (int count = help[i]; count>0; count--) {
				arr[j++] = i;
			}
		}
		delete[] help;
	}

}
