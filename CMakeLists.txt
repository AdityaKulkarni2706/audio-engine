cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "Vcpkg toolchain file")

project(audio-engine)
find_package(SndFile CONFIG REQUIRED)

add_executable(main ./src/main.cpp ./src/AudioFileIO.cpp)
target_include_directories(main PRIVATE ./src)
target_link_libraries(main PRIVATE SndFile::sndfile)
