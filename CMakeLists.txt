cmake_minimum_required(VERSION 3.10)
project(QuantumC VERSION 0.1.0 LANGUAGES C)

# Force C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Define the library
add_library(quantumc SHARED
    src/qc_context.c
    src/qc_session.c
    # i will come back to update this later as the project matures.
)

# set public include directory
target_include_directories(quantumc PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# link against POSIX threads or math if needed
find_package(Threads REQUIRED)
target_link_libraries(quantumc PRIVATE Threads::Threads)
