#ifndef BARON_PATTERN_MATCHING_HPP
#define BARON_PATTERN_MATCHING_HPP

#include <vector>

namespace baron {

	// Helper function for KMP algorithm, preprocesses the pattern
	std::vector<int> prepare_lps(const char *pattern);

	// KMP algorithm; linear comlexity O(strlen(text))
	std::vector<int> pattern_search_kmp(const char *text, const char *pattern);
}

#endif // BARON_PATTERN_MATCHING_HPP
