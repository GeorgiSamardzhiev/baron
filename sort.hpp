#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>

namespace baron {

	template <typename T>
	void insertionSort(T* A, const int& size) {
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
	void selectionSort(T* arr, const int& size) {
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

	void countingSort(int* arr, const int& size);

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
	struct PileElement {
		T element;
		PileElement* backPointer;

		PileElement(T e, PileElement* bp) : element(e), backPointer(bp) {}
	};

	template <typename T>
	class PileCompareGreater {
	public:
		bool operator() (const std::stack<PileElement<T>*>& pile1, const std::stack<PileElement<T>*>& pile2) {
			return pile1.top()->element > pile2.top()->element;
		}
	};

	template <typename T>
	class PileCompareLess {
	public:
		bool operator() (const std::stack<PileElement<T>*>& pile1, const std::stack<PileElement<T>*>& pile2) {
			return pile1.top()->element < pile2.top()->element;
		}
	};

	template <typename T>
	std::pair<std::vector<T>, std::vector<T>> patienceSort(const std::vector<T>& arr) {
		using Pile = std::stack<PileElement<T>*>;
		std::vector<T> longestIncreasingSubsequence;
		std::vector<T> sorted;
		std::vector<Pile> piles({ Pile({ new PileElement<T>(arr[0], nullptr) }) });
		size_t arrSize = arr.size();

		for (int i = 1; i<arrSize; i++) {
			typename std::vector<Pile>::iterator iter = std::lower_bound(piles.begin(), piles.end(), Pile({ new PileElement<T>(arr[i], nullptr) }), PileCompareLess<T>());
			if (iter != piles.end()) {
				iter->push(new PileElement<T>(arr[i], (iter != piles.begin()) ? std::prev(iter)->top() : nullptr));
			} else {
				piles.push_back({ Pile({ new PileElement<T>(arr[i], std::prev(iter)->top()) }) });
			}
		}

		longestIncreasingSubsequence.push_back(piles.back().top()->element);
		for (PileElement<T>* pe = piles.back().top()->backPointer; pe != nullptr; pe = pe->backPointer) {
			longestIncreasingSubsequence.push_back(pe->element);
		}
		std::reverse(longestIncreasingSubsequence.begin(), longestIncreasingSubsequence.end());

		std::priority_queue<Pile, std::vector<Pile>, PileCompareGreater<T>> heap(piles.begin(), piles.end());
		while (!heap.empty()) {
			Pile temp = heap.top();
			sorted.push_back(temp.top()->element);
			heap.pop();
			temp.pop();
			if (!temp.empty()) {
				heap.push(temp);
			}
		}

		return std::make_pair(sorted, longestIncreasingSubsequence);
	}

	template <typename T>
	unsigned int partition(T* arr, unsigned int l, unsigned int h) {
		T pivot = arr[l];
		--l; ++h;

		while (true) {
			do {
				++l;
			} while (arr[l] < pivot);
			do {
				--h;
			} while (arr[h] > pivot);

			if (l >= h) {
				return l;
			}
			std::swap(arr[l], arr[h]);
		}

	}

	template <typename T>
	void quickSort(T* arr, unsigned int l, unsigned int h) {
		while (l<h) {
			unsigned int m = partition(arr, l, h);
			if (m-l < h-m) {
				quickSort(arr, l, m == 0 ? 0 : m-1);
				l = m+1;
			} else {
				quickSort(arr, m+1, h);
				h = m-1;
			}
		}
	}

}

#endif // !SORT_HPP