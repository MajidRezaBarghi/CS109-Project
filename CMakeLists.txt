cmake_minimum_required (VERSION 2.8.12)
project (CS109-Project)


# configure a header file to pass some of the CMake settings
# to the source code
add_compile_options(-std=c++11)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
#configure_file(File  ${PROJECT_SOURCE_DIR}/File  ${PROJECT_BINARY_DIR}/File COPYONLY)
add_executable(main main.cpp ${sources} ${headers})
