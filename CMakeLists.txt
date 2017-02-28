cmake_minimum_required (VERSION 2.6)
project (CS109-Project)


# configure a header file to pass some of the CMake settings
# to the source code
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
add_executable(main main.cpp ${sources} ${headers})
