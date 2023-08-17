# Huffman Archiver

Huffman archiver is a small C++ command line tool and library based on huffman encoding and decoding

## Usage

**Library:**

The library has 2 main functions:

* `Encode` - takes vector of strings (file names that will be compressed) and output file name. Compresses specified files into archive with specified name
* `Decode` - takes archive name. Decompresses specified archive into multiple files

Example:

```c++
Encode({"file_a","file_b","folder_a/file_c"}, "arhcive");
Decode("arhcive");
```

**Command line tool:**

Command line tool has 3 available commands:

* `arhiver -h`  - shows usage info and available commands
* `arhiver -c`  - performs `Encode` on specified args (`[archive_name]` `[file1]` `[file2]` `...`)
* `arhiver -d` - performs `Decode` on specified arg (`[archive_name]`)

## Build

Build process is very simple and will add 2 targets to your cmake project: 
* `huffman_archiver` - library of huffman encoding and decoding
* `archiver` - command line tool for creating huffman encoded archives

To build library:

1. Start by cloning the repository with `git clone https://github.com/Mag1str02/HuffmanArchiver` or adding it as a submodule by `git submodule add https://github.com/Mag1str02/HuffmanArchiver`

To build command line tool:

2. Create build directory by `mkdir build`
3. Move to build dir by `cd build`
4. Configure by `cmake ..`
5. Build by `cmake --build .` 

To use library:

2. Add library directory to your cmake project by `add_subdirectory([PATH_TO_HUFFMAN_ARCHIVER])`
3. Add library `Include` folder to your cmake target by `target_include_directories([YOUR_TARGET] [PATH_TO_HUFFMAN_INCLUDE_FOLDER])`
4. Link library to your cmake target by `target_link_libraries([YOUR_TARGET] huffman_archiver)`