include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests
        tuple_test.cpp
)

# Include src directory so tests can find PixelMath.hpp
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_options(unit_tests PRIVATE ${STRICT_WARNING_FLAGS})
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)

if (ENABLE_COVERAGE)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(unit_tests PRIVATE --coverage -O0 -g)
        target_link_options(unit_tests PRIVATE --coverage)
    endif ()
endif ()

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)
