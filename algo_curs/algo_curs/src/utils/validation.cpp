#include "utils/validation.h"
#include "utils/string_utils.h"
#include <algorithm>
#include <ctime>

static bool isAsciiDigit(char32_t ch) {
    return ch >= U'0' && ch <= U'9';
}

static char32_t toUpperChar(char32_t ch) {
    if (ch >= U'a' && ch <= U'z') return ch - 32;
    if (ch >= U'а' && ch <= U'я') return ch - 32;
    if (ch == U'ё') return U'Ё';
    return ch;
}

static char32_t canonicalCarLetter(char32_t ch) {
    ch = toUpperChar(ch);
    switch (ch) {
        case U'A': case U'А': return U'А';
        case U'B': case U'В': return U'В';
        case U'E': case U'Е': return U'Е';
        case U'K': case U'К': return U'К';
        case U'M': case U'М': return U'М';
        case U'H': case U'Н': return U'Н';
        case U'O': case U'О': return U'О';
        case U'P': case U'Р': return U'Р';
        case U'C': case U'С': return U'С';
        case U'T': case U'Т': return U'Т';
        case U'Y': case U'У': return U'У';
        case U'X': case U'Х': return U'Х';
        default: return 0;
    }
}

bool validateNotEmpty(const std::string& value, const std::string& fieldName, std::string& error) {
    if (trim(value).empty()) {
        error = "Поле \"" + fieldName + "\" не должно быть пустым.";
        return false;
    }
    return true;
}

bool normalizeDriverLicense(const std::string& input, std::string& normalized, std::string& error) {
    auto parts = split(normalizeSpaces(input), ' ');
    if (parts.size() != 3) {
        error = "Формат водительского удостоверения: RR AA NNNNNN, например 77 АВ 123456.";
        return false;
    }

    std::u32string region = utf8ToU32(parts[0]);
    std::u32string series = utf8ToU32(parts[1]);
    std::u32string number = utf8ToU32(parts[2]);
    if (region.size() != 2 || !isAsciiDigit(region[0]) || !isAsciiDigit(region[1])) {
        error = "Код региона должен содержать две цифры.";
        return false;
    }
    if (series.size() != 2) {
        error = "Серия должна содержать две допустимые буквы: А, В, Е, К, М, Н, О, Р, С, Т, У, Х.";
        return false;
    }
    std::u32string canonicalSeries;
    for (char32_t ch : series) {
        char32_t mapped = canonicalCarLetter(ch);
        if (!mapped) {
            error = "Серия содержит недопустимые буквы.";
            return false;
        }
        canonicalSeries.push_back(mapped);
    }
    if (number.size() != 6) {
        error = "Номер удостоверения должен содержать шесть цифр.";
        return false;
    }
    for (char32_t ch : number) {
        if (!isAsciiDigit(ch)) {
            error = "Номер удостоверения должен содержать только цифры.";
            return false;
        }
    }

    normalized = parts[0] + " " + u32ToUtf8(canonicalSeries) + " " + parts[2];
    return true;
}

bool normalizeCarNumber(const std::string& input, std::string& normalized, std::string& error) {
    std::string compact;
    for (unsigned char ch : input) if (!std::isspace(ch)) compact.push_back(static_cast<char>(ch));
    std::u32string u32 = utf8ToU32(compact);

    if (u32.size() != 9 || u32[6] != U'-') {
        error = "Формат госномера: ANNNAA-NN, например А123ВС-77.";
        return false;
    }

    std::u32string result;
    int letterPositions[] = {0, 4, 5};
    int digitPositions[] = {1, 2, 3, 7, 8};
    for (int pos : letterPositions) {
        char32_t mapped = canonicalCarLetter(u32[pos]);
        if (!mapped) {
            error = "Госномер содержит недопустимую букву. Допустимы А, В, Е, К, М, Н, О, Р, С, Т, У, Х.";
            return false;
        }
        u32[pos] = mapped;
    }
    for (int pos : digitPositions) {
        if (!isAsciiDigit(u32[pos])) {
            error = "Цифровые позиции госномера должны содержать только цифры.";
            return false;
        }
    }
    result = u32;
    normalized = u32ToUtf8(result);
    return true;
}

bool validateYear(int year, std::string& error) {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    int currentYear = local ? local->tm_year + 1900 : 2026;
    if (year < 1950 || year > currentYear + 1) {
        error = "Год выпуска должен быть в диапазоне 1950.." + std::to_string(currentYear + 1) + ".";
        return false;
    }
    return true;
}
