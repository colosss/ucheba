#ifndef UTILS_BOYER_MOORE_H
#define UTILS_BOYER_MOORE_H

#include <string>

class BoyerMoore {
public:
    static bool contains(const std::string& text, const std::string& pattern, bool ignoreAsciiCase = true);
    static int findFirst(const std::string& text, const std::string& pattern, bool ignoreAsciiCase = true);
};

#endif
