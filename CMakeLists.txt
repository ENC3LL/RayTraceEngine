cmake_minimum_required(VERSION 3.10)

# Имя проекта и версия
project(RayTracer VERSION 1.0)

# 1. Стандарт C++
# Мы ставим C++17 или C++20. Это даст нам удобные фичи вроде 
# std::optional, std::shared_ptr, filesystem и т.д.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 2. Флаги компиляции (Deep C++ подход)
# Мы хотим, чтобы компилятор был строгим.
# -Wall -Wextra : включают большинство предупреждений.
# -O3 : Максимальная оптимизация (критично для Release сборок).
if(MSVC)
    # Флаги для Visual Studio (Windows)
    add_compile_options(/W4)
else()
    # Флаги для GCC / Clang (Linux, macOS, MinGW)
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# 3. Добавляем исполняемый файл
# Мы говорим: "Собери программу RayTracer из файлов в папке src"
# file(GLOB...) иногда используют, но лучше перечислять файлы вручную 
# или использовать aux_source_directory для контроля. Пока укажем явно:
add_executable(RayTracer src/main.cpp)

# 4. Include директории
# Самый важный момент для новичков. Мы говорим CMake:
# "Когда компилируешь этот таргет, ищи заголовочные файлы (.h) в папке include/"
# PUBLIC означает, что если кто-то зависит от нашей библиотеки, он тоже увидит эти заголовки.
target_include_directories(RayTracer PUBLIC include)