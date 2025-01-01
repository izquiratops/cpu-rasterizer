cmake_minimum_required(VERSION 3.20)
project(cpu-rasterizer)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

file(GLOB_RECURSE RASTERIZER_HEADERS "include/rasterizer/*.hpp")
file(GLOB_RECURSE RASTERIZER_SOURCES "source/*.cpp")

add_executable(cpu-rasterizer
    ${RASTERIZER_HEADERS}
    ${RASTERIZER_SOURCES}
)

target_include_directories(cpu-rasterizer PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(cpu-rasterizer PUBLIC
    ${SDL2_LIBRARIES}
)   