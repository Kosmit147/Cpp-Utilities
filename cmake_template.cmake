cmake_minimum_required(VERSION 4.0)

include("warnings.cmake")
include(CheckIPOSupported)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS FALSE)

project(
    Example
    VERSION 0.0.1
    DESCRIPTION "A description."
    LANGUAGES C CXX
)

# The script expects build type / config to be one of standard CMake build types, that is either Debug, Release,
# RelWithDebInfo or MinSizeRel.

option(BUILD_SHARED_LIBS OFF)

if(NOT GENERATOR_IS_MULTI_CONFIG AND NOT DEFINED CMAKE_BUILD_TYPE)
    message(WARNING "No build type specified. Defaulting to 'Release'.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

check_ipo_supported(RESULT IPO_SUPPORTED)

if(IPO_SUPPORTED)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL ON)
endif()

if(MSVC)
    add_compile_options(
        "/permissive-"     # Standards conformance mode for MSVC compiler.
		"/Zc:preprocessor" # Standards conformance mode for MSVC's preprocessor.
    )

    # Replace /Ob1 with /Ob2 in RelWithDebInfo builds to enable full inlining.
    string(REPLACE "/Ob1" "" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} /Ob2")
    string(REPLACE "/Ob1" "" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}")
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} /Ob2")
endif()

add_executable(
    example
    "main.cpp"
)

set(DEFINITIONS
    $<$<PLATFORM_ID:Windows>:NOMINMAX>
    $<$<CONFIG:Debug>:_DEBUG>
)

add_executable(Example::example ALIAS example)

target_compile_features(example PRIVATE cxx_std_23)
get_compiler_warnings(COMPILER_WARNINGS)
target_compile_options(example PRIVATE ${COMPILER_WARNINGS})
target_precompile_headers(example PRIVATE "pch.hpp")
target_compile_definitions(example PRIVATE ${DEFINITIONS})
set_property(TARGET example PROPERTY COMPILE_WARNING_AS_ERROR ON)