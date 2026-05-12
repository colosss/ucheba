#include "utils/boyer_moore.h"
#include "utils/string_utils.h"
#include <array>
#include <algorithm>

int BoyerMoore::findFirst(const std::string& sourceText, const std::string& sourcePattern, bool ignoreAsciiCase) {
    std::string text = ignoreAsciiCase ? toLowerAscii(sourceText) : sourceText;
    std::string pattern = ignoreAsciiCase ? toLowerAscii(sourcePattern) : sourcePattern;

    const int n = static_cast<int>(text.size());
    const int m = static_cast<int>(pattern.size());
    if (m == 0) return 0;
    if (n < m) return -1;

    std::array<int, 256> badChar{};
    badChar.fill(-1);
    for (int i = 0; i < m; ++i) badChar[static_cast<unsigned char>(pattern[i])] = i;

    int shift = 0;
    while (shift <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) --j;
        if (j < 0) return shift;
        int badIndex = badChar[static_cast<unsigned char>(text[shift + j])];
        shift += std::max(1, j - badIndex);
    }
    return -1;
}

bool BoyerMoore::contains(const std::string& text, const std::string& pattern, bool ignoreAsciiCase) {
    return findFirst(text, pattern, ignoreAsciiCase) >= 0;
}
