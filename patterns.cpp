#include <cstring>
#include "patterns.hpp"

namespace baron {

	std::vector<int> prepare_lps(const char *pattern) {
		size_t pattern_length = strlen(pattern);
		std::vector<int> lps(pattern_length);

		if (pattern_length == 0) {
			return lps;
		}

		lps[0] = 0;

		int i = 1;
		int len = 0;
		while (i < pattern_length) {
			if (pattern[i] == pattern[len]) {
				lps[i++] = ++len;
			} else {
				if (len) {
					len = lps[len - 1];
				} else {
					lps[len] = 0;
					i++;
				}
			}
		}

		return lps;
	}

	std::vector<int> pattern_search_kmp(const char *text, const char *pattern) {
		std::vector<int> result;

		if (text == nullptr || pattern == nullptr) {
			return result;
		}

		size_t pattern_length = strlen(pattern);

		if (pattern_length == 0) {
			return result;
		}

		std::vector<int> lps = prepare_lps(pattern);

		int i = 0;
		int j = 0;

		size_t n = strlen(text);
		while (i < n) {
			if (j == pattern_length) {
				result.push_back(i - j);
				j = lps[j - 1];
			}
			if (text[i] == pattern[j]) {
				++i;
				++j;
			} else {
				if (j) {
					j = lps[j - 1];
				} else {
					++i;
				}
			}
		}
		if (j == pattern_length) {
			result.push_back(i - j);
		}
		return result;
	}

}
