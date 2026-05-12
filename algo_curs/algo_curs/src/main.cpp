#include "ui/console_ui.h"
#include <clocale>
#include <filesystem>
#include <iostream>
#include <cstdlib>

static std::string detectDataDirectory() {
    namespace fs = std::filesystem;
    if (fs::exists("src/data")) return "src/data";
    if (fs::exists("../src/data")) return "../src/data";
    fs::create_directories("src/data");
    return "src/data";
}

int main() {
    std::setlocale(LC_ALL, "");
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
    try {
        ConsoleUI ui(detectDataDirectory());
        ui.run();
    } catch (const std::exception& ex) {
        std::cerr << "Критическая ошибка: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
