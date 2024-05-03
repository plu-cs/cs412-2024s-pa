cmake_minimum_required(VERSION 3.27)
project(lutert)

include(cmake/lutert-cmake-config.cmake)

set( lutert_lib_SOURCES
        src/image.cpp
        src/include/image.h
        src/include/common.h
        src/include/ray.h
        src/camera.cpp
        src/include/camera.h
        src/include/json.h
        src/include/transform.h
        src/include/matchers.h
        src/include/sphere.h
        src/sphere.cpp
        src/include/material.h
        src/lambertian.cpp
        src/metal.cpp
        src/dielectric.cpp
        src/include/random.h
        src/include/spherical.h
        src/include/heatmap.h
        src/progressbar.cpp
        src/include/progressbar.h
        src/surface.cpp
        src/include/materiallib.h
        src/materiallib.cpp
        src/include/scene.h
        src/scene.cpp
        src/parse_scene.cpp
        src/include/quad.h
        src/quad.cpp
)

add_library(lutert_lib ${lutert_lib_SOURCES})
target_link_libraries(lutert_lib
        PUBLIC ${LUTERT_PUBLIC_LIBS}
        PRIVATE ${LUTERT_PRIVATE_LIBS}
)
target_include_directories(lutert_lib
        PUBLIC src/include
)

add_executable(lutert src/main.cpp)
target_link_libraries( lutert PRIVATE lutert_lib )

add_executable(task00 src/task00.cpp)
target_link_libraries( task00 PRIVATE lutert_lib )

add_executable(task01 src/task01.cpp)
target_link_libraries( task01 PRIVATE lutert_lib )

add_executable(task02 src/task02.cpp)
target_link_libraries( task02 PRIVATE lutert_lib )

add_executable(task03 src/task03.cpp)
target_link_libraries( task03 PRIVATE lutert_lib )
target_link_libraries( task03 PRIVATE Catch2::Catch2WithMain )

add_executable(task04 src/task04.cpp)
target_link_libraries( task04 PRIVATE lutert_lib )

add_executable(task05a src/task05a.cpp)
target_link_libraries( task05a PRIVATE lutert_lib )
target_link_libraries( task05a PRIVATE Catch2::Catch2WithMain )

add_executable(task05b src/task05b.cpp)
target_link_libraries( task05b PRIVATE lutert_lib )

add_executable(task06a src/task06a.cpp)
target_link_libraries( task06a PRIVATE lutert_lib )

add_executable(task06b src/task06b.cpp)
target_link_libraries( task06b PRIVATE lutert_lib )
target_link_libraries( task06b PRIVATE Catch2::Catch2WithMain )

add_executable(task07 src/task07.cpp)
target_link_libraries( task07 PRIVATE lutert_lib )
