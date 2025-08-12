cmake_minimum_required(VERSION 3.10)

project(meeting_logger LANGUAGES CXX)

# Add xlnt subdirectory, assuming it's in external/xlnt and has CMakeLists.txt
add_subdirectory(external/xlnt)

# Your executable
add_executable(meeting_logger
    src/main.cpp
)

# Include itlib headers (adjust path if needed)
target_include_directories(meeting_logger PRIVATE
    ${CMAKE_SOURCE_DIR}/external/itlib/include
)

# Link libraries: xlnt and Android log library
target_link_libraries(meeting_logger PRIVATE
    xlnt
    log
)
