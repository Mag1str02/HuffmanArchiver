#pragma once

#include "Encoder.h"
#include "Decoder.h"

using Command = std::vector<std::string>;

class Archiver
{
public:
    Archiver();

    void ProcessCommand(int arg_count, char** args);

    void EncodeData(const std::vector<std::string>& input_files_names, const std::string& output_file_name);
    void DecodeData(const std::string& input_file_name);

private:
    Command command;
    Encoder encoder;
    Decoder decoder;

    bool CheckHelp();
    bool CheckCompression();
    bool CheckDecompression();

    void    ProcessHelp();
    void    ProcessCompression();
    void    ProcessDecompression();
    Command ParseArgs(int arg_count, char** args);
};

void Encode(const std::vector<std::string>& input_files_names, const std::string& output_file_name);
void Decode(const std::string& input_file_name);
