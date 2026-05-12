cmake_minimum_required(VERSION 3.10)
project(algo_curs_car_rental LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(algo_curs
    src/main.cpp
    src/domain/client.cpp
    src/domain/car.cpp
    src/domain/rentalrecord.cpp
    src/repository/client_repository.cpp
    src/repository/car_repository.cpp
    src/repository/rental_repository.cpp
    src/service/rental_service.cpp
    src/ui/console_ui.cpp
    src/utils/string_utils.cpp
    src/utils/boyer_moore.cpp
    src/utils/validation.cpp
    src/structures/avltree.cpp
    src/structures/hashtable.cpp
)

target_include_directories(algo_curs PRIVATE src)
