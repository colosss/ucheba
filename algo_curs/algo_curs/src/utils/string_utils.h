#ifndef UTILS_STRING_UTILS_H
#define UTILS_STRING_UTILS_H

#include <string>
#include <vector>

std::string trim(const std::string& value);
std::vector<std::string> split(const std::string& value, char delimiter);
std::string sanitizeField(const std::string& value);
std::string toLowerAscii(const std::string& value);
std::string normalizeSpaces(const std::string& value);
std::string utf8ToUpperRuEn(const std::string& value);
std::u32string utf8ToU32(const std::string& value);
std::string u32ToUtf8(const std::u32string& value);

#endif
