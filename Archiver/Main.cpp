#include "Archiver.h"
#include <iostream>

int main(int argc, char** argv)
{
    try
    {
        std::ifstream b;
        Archiver      archiver;
        archiver.ProcessCommand(argc, argv);
        std::cout << std::endl;
    } catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}
//"cpp": "cd $dir && cmake CMakeList.txt -S . -B ./build && cd build && make",