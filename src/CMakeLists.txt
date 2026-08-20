add_executable(${PROJECT_NAME} main.cpp
        lib/tuple.hpp
        lib/tuple.cpp
        lib/color.hpp
        lib/color.cpp
        lib/canvas.hpp
        lib/matrix.hpp
        lib/matrix.cpp
        lib/transform.hpp
        lib/transform.cpp
        lib/rays.hpp
        lib/rays.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE ${STRICT_WARNING_FLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
