// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/commandlineparser.hpp"
#include "../include/sequencesearcher.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
    CP::MatrixRowSearcher temp();

    CP::SearchMatrix data;
    std::vector<int> test = {1,2,3,1,1,4,5,6};
    data.push_back(std::move(test));
    CP::SequenceSearcher searcher(data);
    std::cout << "Searcher Created" << std::endl;
    searcher.Search({1,2});
    return 0;
}