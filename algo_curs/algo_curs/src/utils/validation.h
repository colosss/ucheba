#ifndef UTILS_VALIDATION_H
#define UTILS_VALIDATION_H

#include <string>

bool normalizeDriverLicense(const std::string& input, std::string& normalized, std::string& error);
bool normalizeCarNumber(const std::string& input, std::string& normalized, std::string& error);
bool validateYear(int year, std::string& error);
bool validateNotEmpty(const std::string& value, const std::string& fieldName, std::string& error);

#endif
