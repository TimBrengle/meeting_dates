cmake_minimum_required(VERSION 3.15)
project(meeting_dates LANGUAGES CXX)

# =========≈===============================================
# Compiler settings
# =========≈===============================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

message(STATUS "=== Configuring meeting_dates ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# =========≈=========================================
# Local xlnt library
# =========≈=========================================
set(XLNT_DIR "${CMAKE_SOURCE_DIR}/external/xlnt-src")

# Disable xlnt examples/tests/python
set(XLNT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(XLNT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(XLNT_BUILD_PYTHON OFF CACHE BOOL "" FORCE)

# --- Suppress all warnings for external/ ---
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:-w>")
elseif(MSVC)
    add_compile_options("$<$<COMPILE_LANGUAGE:CXX>:/W0>")
endif()

# Include xlnt headers and sources
add_subdirectory("${XLNT_DIR}" "${CMAKE_BINARY_DIR}/xlnt-build")

# Disable warnings for all targets inside external/
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")

file(GLOB_RECURSE external_dirs RELATIVE "${EXTERNAL_DIR}" "${EXTERNAL_DIR}/*/CMakeLists.txt")
foreach (ext_dir ${external_dirs})
    get_filename_component(ext_path "${ext_dir}" DIRECTORY)
    set(full_path "${EXTERNAL_DIR}/${ext_path}")
    if (EXISTS "${full_path}/CMakeLists.txt")
        set_property(DIRECTORY "${full_path}" PROPERTY COMPILE_OPTIONS "-w")
    endif()
endforeach()

# =========≈=========================================
# Project sources
# =========≈=========================================
    file(GLOB_RECURSE PROJECT_SOURCES \
        "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Create executable
add_executable(meeting_dates ${PROJECT_SOURCES})

# Include directories
target_include_directories(meeting_dates PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    "${XLNT_DIR}/include"
)

# Link xlnt
target_link_libraries(meeting_dates PRIVATE xlnt)

# =========≈=========================================
# Warnings (our code only)
# =========≈=========================================
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(meeting_dates PRIVATE
        -Wall -Wextra -Wpedantic -Werror
        -Wno-switch-default
        -Wunused-but-set-variable
        -Wsuggest-destructor-override
        -Wunsafe-buffer-usage
        -Wunsafe-buffer-usage-in-libc-call
        -Wsuggest-override
    )
elseif(MSVC)
    target_compile_options(meeting_dates PRIVATE /W4 /WX)
endif()

