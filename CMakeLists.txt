cmake_minimum_required(VERSION 3.15)
project(meeting_dates LANGUAGES CXX)

# =========≈===============================================
# Compiler settings
# =========≈===============================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

message(STATUS "=== Configuring meeting_dates ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# =========≈===============================================
# Local xlnt library
# =========≈===============================================
set(XLNT_DIR "${CMAKE_SOURCE_DIR}/external/xlnt-src")

# Disable xlnt examples/tests/python
set(XLNT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(XLNT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(XLNT_BUILD_PYTHON OFF CACHE BOOL "" FORCE)

# Include xlnt headers and sources
add_subdirectory("${XLNT_DIR}" "${CMAKE_BINARY_DIR}/xlnt-build")

# =========≈===============================================
# Project sources
# =========≈===============================================
file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable(meeting_dates ${PROJECT_SOURCES})

# Include directories
target_include_directories(meeting_dates PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${XLNT_DIR}/include"
)

# Link xlnt
target_link_libraries(meeting_dates PRIVATE xlnt)

# =========≈===============================================
# Warnings (our code only)
# =========≈===============================================
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(meeting_dates PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        -Wno-unsafe-buffer-usage
    )
elseif(MSVC)
    target_compile_options(meeting_dates PRIVATE /W4 /WX)
endif()

