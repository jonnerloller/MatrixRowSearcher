// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include "../include/commandlineoptions.hpp"
#include "../include/unittests.hpp"
#include <iostream>
#include <functional>
#include <cstring>
#include <limits>
#include <fstream>
#include <iterator>
#include <string>
#include <cstdlib>

CP::RowData ConvertCommandLineArgumentsToInt(CP::CommandLineOptions::ArgumentPack&& arguments)
{
    CP::RowData convertedArguments;
    convertedArguments.reserve(arguments.size());
    for (const auto& arg : arguments)
    {
        convertedArguments.push_back(std::atoi(arg.c_str()));
    }
    return convertedArguments;
}

void RunUnitTests(const std::string&, CP::CommandLineOptions::ArgumentPack&&)
{
    CP::RunSequenceSearchUnitTests();
    CP::RunExistSearchUnitTests();
}

void PerformSequenceSearch(const std::string& argIdentifier, CP::CommandLineOptions::ArgumentPack&& arguments)
{
    CP::RowData convertedArguments = ConvertCommandLineArgumentsToInt(std::move(arguments));
    CP::MatrixRowSearcher& matrixRowSearcher = CP::MatrixRowSearcher::GetInstance();
    matrixRowSearcher.Search(argIdentifier, convertedArguments);
}

void ProcessCommandLineArgument(std::string arg)
{
    // We can assume arg is not empty if not it won't be a command line arg.
    // check for '/'. That is our special delimiter.
    if (arg[0] == '/')
    {
        size_t functionSeperatorPos = arg.find(":");
        bool hasArguments = functionSeperatorPos != std::numeric_limits<size_t>::max();
        // skip the initial /
        // also we don't want to store the ':' so we have to do an offset.
        std::string commandLineOptionName = arg.substr(1, functionSeperatorPos - 1);
        
        size_t argumentSeperatorPos = arg.find(",", functionSeperatorPos);
        
        // we don't want to start with ',' so we do an offset
        size_t lastArgumentSeperatorPos = functionSeperatorPos + 1;
        std::string sequenceArgumentString;
        std::vector<std::string> arguments;
        // we process it in based on the comma.
        while (argumentSeperatorPos != std::numeric_limits<size_t>::max())
        {
            sequenceArgumentString = arg.substr(lastArgumentSeperatorPos, argumentSeperatorPos - lastArgumentSeperatorPos);
           
            arguments.push_back(sequenceArgumentString);
            // we don't want to start with ',' so we do an offset
            lastArgumentSeperatorPos = argumentSeperatorPos + 1;
            argumentSeperatorPos = arg.find(",", lastArgumentSeperatorPos);
        }
         //we have to process the last argument.
        if(hasArguments)
        {
            // have to do a -1 since string iteratres from 0 -> strlen - 1
            sequenceArgumentString = arg.substr(lastArgumentSeperatorPos, arg.length() - 1);
            arguments.push_back(sequenceArgumentString);
        }
        CP::CommandLineOptions::GetInstance().RunCommandLine(commandLineOptionName, std::move(arguments));
        
    }
    // Assumes that the first argument is the filename to load.
    else
    {
        CP::MatrixRowSearcher::LoadFile(arg);
    }
}

void InitCommandLineArguments()
{
    CP::CommandLineOptions& commandLineOptions = CP::CommandLineOptions::GetInstance();
    commandLineOptions.AddCommandLineOption("sequenceSearch", PerformSequenceSearch);
    commandLineOptions.AddCommandLineOption("existSearch", PerformSequenceSearch);

    commandLineOptions.AddCommandLineOption("unitTests", RunUnitTests);
}

int main(int argc, char* argv[])
{
    
    // argv [1] = inputFile 
    // argv [2] = /searchSequence:1,2,3,4

    InitCommandLineArguments();

    for (int arg = 1; arg < argc; ++arg)
    {
        ProcessCommandLineArgument(std::string(argv[arg]));
    }

    CP::MatrixRowSearcher& matrixRowSearcher = CP::MatrixRowSearcher::GetInstance();
    CP::RowIndices indices = matrixRowSearcher.Search("sequenceSearch",{1,2});

    indices = matrixRowSearcher.Search("sequenceSearch",{ 0 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 8 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 7 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 5,6,7 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 1,1,4,5 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 1,2,3,1,1,4,5,6,7 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 1,1,4,6 });
    indices = matrixRowSearcher.Search("sequenceSearch",{ 2,3,1,1,4,5,6,7 });

    indices = matrixRowSearcher.Search("existSearch",{ 0 });
    indices = matrixRowSearcher.Search("existSearch",{ 2,7 });
    indices = matrixRowSearcher.Search("existSearch",{ 1,6 });
    indices = matrixRowSearcher.Search("existSearch",{ 2,3,8 });
    indices = matrixRowSearcher.Search("existSearch",{ 4,4,4,4,4,1 });
    
    return 0;
}