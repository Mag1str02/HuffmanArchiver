cmake_minimum_required(VERSION 3.16)

project(archiver)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(huffman_archiver
    Source/Encoder.cpp
    Source/Decoder.cpp
    Source/BitWriter.cpp
    Source/BitReader.cpp
    Source/HuffmanTree.cpp
    Source/Structures.cpp
    Source/Archiver.cpp
)
target_include_directories(huffman_archiver PUBLIC Include)


add_executable(archiver
    Archiver/Main.cpp
)
target_include_directories(archiver PUBLIC Include)
target_link_libraries(archiver huffman_archiver)
