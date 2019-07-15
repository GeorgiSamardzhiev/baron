#include <stdio.h>
#include <cstring>
#include "patterns.h"

namespace baron {
    std::vector<int> prepare_lps(const char *pattern) {
        int pattern_length = strlen(pattern);
        std::vector<int> lps(pattern_length);
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

        std::vector<int> lps = prepare_lps(pattern);
        int pattern_length = strlen(pattern);
        int i = 0;
        int j = 0;
        while (i < strlen(text)) {
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
        return result;
    }
}
