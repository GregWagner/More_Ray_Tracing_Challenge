cmake_minimum_required(VERSION 3.14)
project(RaylibPixel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable code coverage instrumentation" OFF)

include(FetchContent)

# Fetch raylib at root so subdirectories can link to it
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
FetchContent_MakeAvailable(raylib)

# Common GCC / Clang warning flags shared across targets
set(STRICT_WARNING_FLAGS)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  list(APPEND STRICT_WARNING_FLAGS
        -Wall -Wextra -Wpedantic -Werror -Wshadow
        -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Wconversion -Wsign-conversion -Wnull-dereference
        -Wdouble-promotion
    )
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    list(APPEND STRICT_WARNING_FLAGS
            -Wlogical-op -Wduplicated-cond -Wduplicated-branches
        )
  endif()
endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)
