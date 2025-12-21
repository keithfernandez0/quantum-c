cmake_minimum_required(VERSION 3.10)
project(QuantumC VERSION 0.1.0 LANGUAGES C)

# Enforce POSIX and C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF) # Keep it pure C99/POSIX

# Compiler flags
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror -Wpedantic)
endif()

# 1. Define the Library
add_library(quantumc SHARED 
    src/qc_session.c
)

# 2. Tell the library where its own headers are
target_include_directories(quantumc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 3. Define a Test Executable
add_executable(test_session tests/test_session.c)
target_link_libraries(test_session PRIVATE quantumc)
