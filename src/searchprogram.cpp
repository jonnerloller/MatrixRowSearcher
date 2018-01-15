// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include <iostream>
#include <functional>
#include <cstring>
#include <limits>
#include <fstream>
#include <iterator>
#include <string>
#include <cstdlib>
void LoadFile(const std::string& str)
{
    std::ifstream file(str);
    std::istream_iterator<int> it(file);
    std::istream_iterator<int> eof;
    std::vector<int> data;
    std::copy(it, eof, std::back_inserter(data));
    CP::SearchMatrix searchMatrix;
    // First 2 arguments are Width and Height
    if (data.size() > 2)
    {
        int width = data[0];
        int height = data[1];

        // We read all the matrix data together.
        // the first row starts after the first 2 arguments
        // we need to offset each row and copy the data.
        int rowOffset = 2;
        searchMatrix.resize(height);
        for (int i = 0; i < height; ++i)
        {
            searchMatrix[i].resize(width);
            std::copy(data.begin() + rowOffset, data.begin() + rowOffset + width, searchMatrix[i].begin());
            rowOffset += width;
        }
        std::shared_ptr<CP::SearchData> searchData = std::make_shared<CP::SearchData>(std::move(searchMatrix));
        CP::MatrixRowSearcher& matrixRowSearcher = CP::MatrixRowSearcher::GetInstance();
        matrixRowSearcher.SetSearchData(searchData);
    }
}

void ProcessCommandLineArgument(std::string arg)
{
    // We can assume arg is not empty if not it won't be a command line arg.
    // check for '/'. That is our special delimiter.
    if (arg[0] == '/')
    {
        size_t functionSeperatorPos = arg.find(":");
        // skip the initial /
        // also we don't want to store the ':' so we have to do an offset.
        std::string searchFunctionName = arg.substr(1, functionSeperatorPos - 1);
        
        size_t argumentSeperatorPos = arg.find(",", functionSeperatorPos);
        
        // we don't want to start with ',' so we do an offset
        size_t lastArgumentSeperatorPos = functionSeperatorPos + 1;
        std::string sequenceArgumentString;
        CP::RowData sequenceArguments;
        // we process it in based on the comma.
        while (argumentSeperatorPos != std::numeric_limits<size_t>::max())
        {
            sequenceArgumentString = arg.substr(lastArgumentSeperatorPos, argumentSeperatorPos - lastArgumentSeperatorPos);
            CP::SearchValue searchArgumentValue = std::atoi(sequenceArgumentString.c_str());
            sequenceArguments.push_back(searchArgumentValue);
            // we don't want to start with ',' so we do an offset
            lastArgumentSeperatorPos = argumentSeperatorPos + 1;
            argumentSeperatorPos = arg.find(",", lastArgumentSeperatorPos);
        }
         //we have to process the last argument.
        {
            // have to do a -1 since string iteratres from 0 -> strlen - 1
            sequenceArgumentString = arg.substr(lastArgumentSeperatorPos, arg.length() - 1);
            CP::SearchValue searchArgumentValue = std::atoi(sequenceArgumentString.c_str());
            sequenceArguments.push_back(searchArgumentValue);
        }
        CP::MatrixRowSearcher& matrixRowSearcher = CP::MatrixRowSearcher::GetInstance();
        matrixRowSearcher.Search(searchFunctionName, sequenceArguments);
    }
    // Assumes that the first argument is the filename to load.
    else
    {
        LoadFile(arg);
    }
}

int main(int argc, char* argv[])
{
    
    // argv [1] = inputFile 
    // argv [2] = /searchSequence:1,2,3,4

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