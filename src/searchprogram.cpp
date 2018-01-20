// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include "../include/commandlineoptions.hpp"
#include "../include/unittests.hpp"
#include "../include/timer.hpp"
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
    CP::Timer timer;
    timer.StartTimer();
    CP::RunSequenceSearchUnitTests();
    CP::RunExistSearchUnitTests();
    CP::RunClosestSearchUnitTests();
    std::cout << "Tests took " << timer.SplitNanoseconds().count() << "ns" << std::endl;
}

void RunLargeTests(const std::string&, CP::CommandLineOptions::ArgumentPack&&)
{
    CP::RunLargeTests();
}

void SetInputData(const std::string& argIdentifier, CP::CommandLineOptions::ArgumentPack&& arguments)
{
    if (argIdentifier == "inputRaw")
    {
        if (arguments.size())
        {
            CP::MatrixRowSearcher::LoadFile(arguments[0]);
        }
    }
    else if(argIdentifier == "inputEncrypted")
    {
        if (arguments.size() == 2)
        {
            std::string outputFileName = arguments[0];
            int key = atoi(arguments[1].c_str());
            CP::MatrixRowSearcher::LoadEncryptedFile(arguments[0],key);
        }
    }
}

void SetDisplayOption(const std::string&, CP::CommandLineOptions::ArgumentPack&& arguments)
{
    if (arguments.size())
    {
        if (arguments[0] == "none")
        {
            CP::MatrixRowSearcher::GetInstance().SetDisplayOption(CP::MatrixRowSearcher::DISPLAY_NONE);
        }
        else if (arguments[0] == "index")
        {
            CP::MatrixRowSearcher::GetInstance().SetDisplayOption(CP::MatrixRowSearcher::DISPLAY_ROW_INDEX_ONLY);
        }
        else if (arguments[0] == "all")
        {
            CP::MatrixRowSearcher::GetInstance().SetDisplayOption(CP::MatrixRowSearcher::DISPLAY_ROW_INDEX_AND_DATA);
        }
    }
}

void EncrpytFile(const std::string&, CP::CommandLineOptions::ArgumentPack&& arguments)
{
    if (arguments.size() == 3)
    {
        std::string inputFileName = arguments[0];
        std::string outputFileName = arguments[1];
        int key = atoi(arguments[2].c_str());

        CP::MatrixRowSearcher::GetInstance().EncryptFile(inputFileName, outputFileName, key);
        return;
    }
    std::cerr << "Invalid number of args for encrypt" << std::endl;
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
}

void InitCommandLineArguments()
{
    CP::CommandLineOptions& commandLineOptions = CP::CommandLineOptions::GetInstance();
    commandLineOptions.AddCommandLineOption("sequenceSearch", PerformSequenceSearch,"/sequenceSearch:x,y,z [Checks to see if our integer sequence x,y,z can be found in our input data");
    commandLineOptions.AddCommandLineOption("existSearch", PerformSequenceSearch, "/existSearch:x,y,z [Checks to see if all integers in the integer sequence x,y,z can be found in our input data.");
    commandLineOptions.AddCommandLineOption("closestSearch", PerformSequenceSearch, "/existSearch:x,y,z [Get's the row with the closest match to integer sequence x,y,z");

    commandLineOptions.AddCommandLineOption("unitTests", RunUnitTests,"/unitTests [Run Basic unit tests]");
    commandLineOptions.AddCommandLineOption("largeTests", RunLargeTests,"/largeTests [Run Large unit test]");
    commandLineOptions.AddCommandLineOption("inputRaw", SetInputData,"/inputRaw:\"filename\" [Loads and preprocess input data]");
    commandLineOptions.AddCommandLineOption("inputEncrypted", SetInputData, "/inputEncrypted:\"filename\",integerkey [Loads encrpyted data, and decryps it using a secret key]");
    commandLineOptions.AddCommandLineOption("encrypt", EncrpytFile, "/encrypt:\"inputfilename\",\"outputfilename\",integerkey [Loads a set of data, encrypts it using the secret key, and dumps the contents to a specified output file]");
    commandLineOptions.AddCommandLineOption("displayOption", SetDisplayOption, "/displayOption:none|index|all, [Sets options to control the output]");
}

int main(int argc, char* argv[])
{
    InitCommandLineArguments();

    if (argc <= 1)
    {
        CP::CommandLineOptions::GetInstance().DumpCommandLineOptions();
    }

    for (int arg = 1; arg < argc; ++arg)
    {
        ProcessCommandLineArgument(std::string(argv[arg]));
    }
    return 0;
}