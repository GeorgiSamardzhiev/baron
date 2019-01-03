#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <stack>
#include <queue>

namespace baron {

	template <typename T>
	void insertionSort(T* A, int& size) {
		for (int i = 1; i<size; i++) {
			T pivot = A[i];
			int j = 0;
			for (j; j<i && A[j]<pivot; j++) {}
			for (int k = i; k>j; k--) {
				A[k] = A[k-1];
			}
			A[j] = pivot;
		}
	}

	template <typename T>
	void selectionSort(T* arr, int& size) {
		for (int i = 0; i < size - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < size; j++) {
				if (arr[j] < arr[minIndex]) {
					minIndex = j;
				}
			}
			T tmp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = tmp;
		}
	}

	void countingSort(int* arr, int& size) {
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
	}

	template <class C>
	void split(C& l, C& l1, C& l2) {
		C* addNow = &l1, *addLater = &l2;
		for (typename C::iterator it = l.begin(); it != l.end(); ++it) {
			addNow->push_back(*it);
			std::swap(addNow, addLater);
		}
	}

	template <class C>
	void merge(C& l, C& l1, C& l2) {
		typename C::iterator it1 = l1.begin();
		typename C::iterator it2 = l2.begin();
		while (it1 != l1.end() && it2 != l2.end())
			if (*it1 < *it2) {
				l.push_back(*it1);
				++it1;
			} else {
				l.push_back(*it2);
				++it2;
			}
		while (it1 != l1.end()) {
			l.push_back(*it1);
			++it1;
		}while (it2 != l2.end()) {
			l.push_back(*it2);
			++it2;
		}
	}

	template <class C>
	void mergeSort(C& l) {
		if (l.size() <=1)
			return;
		C l1, l2;
		split(l, l1, l2);
		mergeSort(l1);
		mergeSort(l2);
		l.clear();
		merge(l, l1, l2);
	}

	template <typename T>
	class PileCompare {
	public:
		bool operator() (const std::stack<T>& pile1, const std::stack<T>& pile2) {
			return pile1.top() > pile2.top();
		}
	};

	template <typename T>
	std::vector<T> patienceSort(std::vector<T>& arr) {
		std::vector<T>  longestIncreasingSubsequence;
		std::vector<std::stack<T>> piles;
		std::stack<T> first;
		first.push(arr[0]);
		piles.push_back(first);
		bool pushed = false;
		int size = arr.size();
		for (int i = 1; i<size; i++) {
			for (std::stack<T>& stack: piles) {
				if (arr[i]<stack.top()) {
					stack.push(arr[i]);
					pushed = true;
					break;
				}
			}
			if (!pushed) {
				if (longestIncreasingSubsequence.empty()) {
					longestIncreasingSubsequence.push_back(piles[0].top());
				}
				longestIncreasingSubsequence.push_back(arr[i]);
				std::stack<T> nextPile;
				nextPile.push(arr[i]);
				piles.push_back(nextPile);
			}
			pushed = false;
		}

		arr.clear();

		std::priority_queue<std::stack<T>, std::vector<std::stack<T>>, PileCompare<T>> heap;

		for (std::stack<T>& pile : piles) {
			heap.push(pile);
		}

		while (!heap.empty()) {
			std::stack<T> temp = heap.top();
			arr.push_back(temp.top());
			heap.pop();
			temp.pop();
			if (!temp.empty()) {
				heap.push(temp);
			}
		}

		return longestIncreasingSubsequence;
	}
}

#endif // !SORT_HPP