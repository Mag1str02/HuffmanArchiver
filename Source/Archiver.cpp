#include "Archiver.h"
#include <iostream>
#include <vector>

Archiver::Archiver() {}

void Archiver::ProcessCommand(int arg_count, char** args)
{
    command = ParseArgs(arg_count, args);
    if (arg_count == 1)
    {
        std::cout << "I don't know what to do. -_-" << std::endl << "Try ./archiver -h";
        return;
    }
    if (command[1] == "-h")
    {
        if (CheckHelp())
        {
            ProcessHelp();
        }
    }
    else if (command[1] == "-c")
    {
        if (CheckCompression())
        {
            ProcessCompression();
        }
    }
    else if (command[1] == "-d")
    {
        if (arg_count == 2)
        {
            std::cout << "Not enough arguments";
            return;
        }
        if (arg_count > 3)
        {
            std::cout << "To much arguments";
            return;
        }
        std::ifstream check(command[2]);
        if (check.is_open())
        {
            check.close();
            try
            {
                std::cout << "Unzipping..." << std::endl;
                DecodeData(command[2]);
            } catch (...)
            {
                std::cout << "Unzipping failed.";
            }
            std::cout << "Unzipping success!";
        }
        else
        {
            std::cout << "Can't open/find archive.";
        }
    }
    else
    {
        std::cout << "Wrong Command";
        return;
    }
}

bool Archiver::CheckHelp()
{
    if (command.size() > 2)
    {
        std::cout << "To much arguments";
        return false;
    }
    return true;
}
bool Archiver::CheckCompression()
{
    if (command.size() <= 3)
    {
        std::cout << "Not enough arguments";
        return false;
    }
    return true;
}
bool Archiver::CheckDecompression() { return true; }

void Archiver::ProcessHelp()
{
    std::cout << "Usage:" << std::endl
              << "    1) Put the files you want to archive/unzip in the same folder with the archiver." << std::endl
              << "    2) Go to the archiver directory by cd." << std::endl
              << "    3) Run command by patter: ./archiver [command] [arg1] ..." << std::endl
              << std::endl
              << "Available commands:" << std::endl
              << "    -c: Archives the specified files to an archive." << std::endl
              << "        Requires at least two arguments: [archive_name] [file_name1] [file_name2] ... " << std::endl
              << "    -d: Unzips specified file." << std::endl
              << "        Requires one argument: [archive_name] " << std::endl
              << "    -h: You know what this command does.";
}
void Archiver::ProcessCompression()
{
    std::vector<size_t> wrong_files_id;
    std::ifstream       check;

    for (size_t i = 3; i < command.size(); ++i)
    {
        check.open(command[i]);
        if (!check.is_open())
        {
            wrong_files_id.push_back(i);
        }
        else
        {
            check.close();
        }
    }
    if (wrong_files_id.size() > 0)
    {
        std::cout << "Can't open/find following files:";
        for (const auto& id : wrong_files_id)
        {
            std::cout << " " << command[id];
        }
    }
    else
    {
        std::vector<std::string>::iterator begin = command.begin();
        std::advance(begin, 3);
        std::ifstream check_output(command[2]);
        if (check_output.is_open())
        {
            check_output.close();
            std::cout << "File \"" << command[2] << "\" already exists. Do you want to overwrite it? [y/n]: ";
            if (std::cin.get() == 'y')
            {
                EncodeData(std::vector<std::string>(begin, command.end()), command[2]);
            }
            else
            {
                std::cout << "Process aborted.";
            }
        }
        else
        {
            EncodeData(std::vector<std::string>(begin, command.end()), command[2]);
        }
    }
}
void Archiver::ProcessDecompression() {}

void Archiver::EncodeData(const std::vector<std::string>& input_files_names, const std::string& output_file_name)
{
    try
    {
        std::ofstream                      output_stream(output_file_name);
        std::vector<std::ifstream>         input_streams(command.size() - 3);
        std::vector<std::string>::iterator begin = command.begin();
        std::advance(begin, 3);

        for (size_t i = 3; i < command.size(); ++i)
        {
            input_streams[i - 3].open(command[i]);
        }
        std::cout << "Archiving..." << std::endl;
        encoder.EncodeData(input_streams, output_stream, input_files_names);
        std::cout << "Archiving success!";
    } catch (...)
    {
        std::cout << "Archiving failed.";
    }
}
void Archiver::DecodeData(const std::string& input_file_name) { decoder.DecodeData(input_file_name); }

Command Archiver::ParseArgs(int arg_count, char** args)
{
    Command command;
    for (size_t i = 0; i < arg_count; ++i)
    {
        command.push_back(std::string(args[i]));
    }
    return command;
}

void Encode(const std::vector<std::string>& input_files_names, const std::string& output_file_name)
{
    Archiver archiver;
    archiver.EncodeData(input_files_names, output_file_name);
}
void Decode(const std::string& input_file_name)
{
    Archiver archiver;
    archiver.DecodeData(input_file_name);
}
