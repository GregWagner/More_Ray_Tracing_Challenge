add_executable(${PROJECT_NAME} main.cpp
        tuple.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(${PROJECT_NAME} PRIVATE ${STRICT_WARNING_FLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
