#include "utils/string_utils.h"
#include <algorithm>
#include <cctype>
#include <codecvt>
#include <locale>
#include <sstream>

std::string trim(const std::string& value) {
    size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) start++;
    size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) end--;
    return value.substr(start, end - start);
}

std::vector<std::string> split(const std::string& value, char delimiter) {
    std::vector<std::string> result;
    std::string current;
    std::stringstream ss(value);
    while (std::getline(ss, current, delimiter)) result.push_back(current);
    if (!value.empty() && value.back() == delimiter) result.emplace_back();
    return result;
}

std::string sanitizeField(const std::string& value) {
    std::string result;
    for (char ch : value) {
        if (ch == '|' || ch == '\n' || ch == '\r') result += ' ';
        else result += ch;
    }
    return normalizeSpaces(trim(result));
}

std::string toLowerAscii(const std::string& value) {
    std::string result = value;
    for (char& ch : result) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    return result;
}

std::string normalizeSpaces(const std::string& value) {
    std::string result;
    bool inSpace = false;
    for (unsigned char ch : value) {
        if (std::isspace(ch)) {
            if (!inSpace) result += ' ';
            inSpace = true;
        } else {
            result += static_cast<char>(ch);
            inSpace = false;
        }
    }
    return trim(result);
}

std::u32string utf8ToU32(const std::string& value) {
    try {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.from_bytes(value);
    } catch (...) {
        std::u32string result;
        for (unsigned char ch : value) result.push_back(ch);
        return result;
    }
}

std::string u32ToUtf8(const std::u32string& value) {
    try {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(value);
    } catch (...) {
        std::string result;
        for (char32_t ch : value) if (ch <= 127) result.push_back(static_cast<char>(ch));
        return result;
    }
}

static char32_t upperOne(char32_t ch) {
    if (ch >= U'a' && ch <= U'z') return ch - 32;
    if (ch >= U'а' && ch <= U'я') return ch - 32;
    if (ch == U'ё') return U'Ё';
    return ch;
}

std::string utf8ToUpperRuEn(const std::string& value) {
    std::u32string u32 = utf8ToU32(value);
    for (char32_t& ch : u32) ch = upperOne(ch);
    return u32ToUtf8(u32);
}
