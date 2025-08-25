cmake_minimum_required(VERSION 3.15)
project(meeting_dates VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Option to rebuild dependencies from source
option(BUILD_DEPS_FROM_SOURCE "Build dependencies from source" OFF)

# ----- Dependencies -----
if(BUILD_DEPS_FROM_SOURCE)
    # xlnt source
    add_subdirectory(external/xlnt)
else()
    # Use system libraries
    find_package(ZLIB REQUIRED)
    find_package(minizip REQUIRED)
    find_package(itlib REQUIRED)
    find_package(xlnt REQUIRED)
endif()

# ----- Executable -----
add_executable(meeting_logger
    src/main.cpp
    src/excel_utilities.cpp
)

# ----- Link libraries -----
if(BUILD_DEPS_FROM_SOURCE)
    target_link_libraries(meeting_logger PRIVATE xlnt itlib)
else()
    target_link_libraries(meeting_logger PRIVATE
        ${XLNT_LIB}
        ${ITLIB_LIB}
        ${MINIZIP_LIB}
        ${ZLIB_LIB}
    )
endif()

# ----- Include directories -----
target_include_directories(meeting_logger PRIVATE
    src
    ${XLNT_INCLUDE_DIR}
    ${ITLIB_INCLUDE_DIR}
    ${MINIZIP_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)
