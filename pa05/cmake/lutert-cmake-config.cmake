
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
            FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use the CPM package manager
# https://github.com/cpm-cmake/CPM.cmake
include(${CMAKE_CURRENT_LIST_DIR}/get_cpm.cmake)

# Dependencies
set(LUTERT_PUBLIC_LIBS)
set(LUTERT_PRIVATE_LIBS)

# Catch 2
CPMAddPackage(
        NAME Catch2
        GITHUB_REPOSITORY catchorg/Catch2
        VERSION 3.5.2
)

# TinyObjLoader
CPMAddPackage(
        NAME tinyobjloader
        GITHUB_REPOSITORY tinyobjloader/tinyobjloader
        GIT_TAG cab4ad7254cbf7eaaafdb73d272f99e92f166df8
        DOWNLOAD_ONLY YES
)
if(tinyobjloader_ADDED)
    add_library(tinyobjloader INTERFACE IMPORTED)
    target_include_directories(tinyobjloader INTERFACE "${tinyobjloader_SOURCE_DIR}/")
    list(APPEND LUTERT_PUBLIC_LIBS tinyobjloader)
endif()

# Linalg
CPMAddPackage("gh:sgorsten/linalg@2.2")
if(linalg_ADDED)
    add_library(linalg INTERFACE IMPORTED)
    target_include_directories(linalg INTERFACE "${linalg_SOURCE_DIR}")
    list(APPEND LUTERT_PUBLIC_LIBS linalg)
endif()

# FMT
CPMAddPackage(
        NAME fmt
        URL https://github.com/fmtlib/fmt/releases/download/10.2.1/fmt-10.2.1.zip
)
if (fmt_ADDED)
    list(APPEND LUTERT_PUBLIC_LIBS fmt)
endif()

CPMAddPackage("gh:nothings/stb#f4a71b13373436a2866c5d68f8f80ac6f0bc1ffe")
if(stb_ADDED)
    add_library(stb INTERFACE IMPORTED)
    target_include_directories(stb INTERFACE "${stb_SOURCE_DIR}")
    list(APPEND LUTERT_PRIVATE_LIBS stb)
endif()

# PCG32
CPMAddPackage(
        NAME pcg32
        GITHUB_REPOSITORY wjakob/pcg32
        GIT_TAG 70099eadb86d3999c38cf69d2c55f8adc1f7fe34
        DOWNLOAD_ONLY YES
)
if (pcg32_ADDED)
    add_library(pcg32 INTERFACE IMPORTED)
    target_include_directories(pcg32 INTERFACE ${pcg32_SOURCE_DIR})
    list(APPEND LUTERT_PUBLIC_LIBS pcg32)
endif()


# JSON
CPMAddPackage(
        NAME nlohmann_json
        VERSION 3.11.3
        # the git repo is incredibly large, so we download the archived include directory
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/include.zip
        URL_HASH SHA256=a22461d13119ac5c78f205d3df1db13403e58ce1bb1794edc9313677313f4a9d
)
if (nlohmann_json_ADDED)
    add_library(nlohmann_json INTERFACE IMPORTED)
    target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
    list(APPEND LUTERT_PUBLIC_LIBS nlohmann_json)
endif()
