cmake_minimum_required(VERSION 3.15)
project(FiguresProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Экспортировать compile_commands.json для clangd / cpptools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Автоматическое подключение Google Test
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# Для Windows нужно предотвратить переопределение макросов Windows.h
if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Основная программа
add_executable(figures_main
    src/main.cpp
    src/point.h
    src/array.h
    src/figure.h
    src/figures.h
)

# Тесты
add_executable(test_figures
    tests/test_figures.cpp
    src/point.h
    src/array.h
    src/figure.h
    src/figures.h
)

# Подключение директорий с исходниками
target_include_directories(figures_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(test_figures PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Связывание тестов с Google Test
target_link_libraries(test_figures PRIVATE GTest::gtest GTest::gtest_main)

# Добавление тестов в CTest
gtest_discover_tests(test_figures)

# Настройка компилятора
target_compile_features(figures_main PRIVATE cxx_std_20)
target_compile_options(figures_main PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

target_compile_features(test_figures PRIVATE cxx_std_20)
target_compile_options(test_figures PRIVATE 
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
)

# Информация о проекте
message(STATUS "=== Figures Project Configuration ===")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Main executable: figures_main")
message(STATUS "Test executable: test_figures")
message(STATUS "======================================")