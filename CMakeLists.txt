
cmake_minimum_required(VERSION 3.24)
set(COMPILE_FLAGS "-g")
set(CMAKE_CXX_COMPILER /usr/bin/clang)
project(atomTest)
set (CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
add_executable(test ${SOURCES})

target_link_libraries(test sdl2 sdl2_image sdl2_mixer glew)

#Use basic linker not whatever garbage cmake gives you
set(CMAKE_LINKER "/usr/bin/g++")
set(CMAKE_LINKER_FLAGS "${LINKER_SCRIPT}")
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> -L/usr/local/opt/llvm/lib/unwind -lunwind  -g -DDEBUG ${CMAKE_LINKER_FLAGS} <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
add_definitions(-DHOT_RELOAD)
target_include_directories(test PUBLIC "include" "libs")
target_link_libraries(test "-framework openGl")
