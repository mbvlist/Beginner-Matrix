# CMakeList.txt : CMake project for Matrix, include source and define
# project specific logic here.
#
# 3.30 is minimum for C++20 modules
cmake_minimum_required (VERSION 3.30 FATAL_ERROR)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# UUID to enable CMake's `import std` handling
# it may potentially change with CMake versions
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508") 

set(CMAKE_CXX_STANDARD 23) # cmake doesn't have modules in C++20
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_MODULE_STD 1) # enable STD

project ("Main" LANGUAGES CXX)

add_library(Matrix)
target_sources(Matrix
  PUBLIC
    FILE_SET CXX_MODULES FILES Matrix.cppm)

# Must be C++23 until CMake merges `import std` as a C++20 extension
target_compile_features(Matrix
  PRIVATE   cxx_std_23
  INTERFACE cxx_std_20)

# Add source to this project's executable.
add_executable (Main
	"main.cpp"
)
target_link_libraries(Main PRIVATE Matrix)

# Must be C++23 until CMake merges `import std` as a C++20 extension
target_compile_features(Main PRIVATE cxx_std_23)

