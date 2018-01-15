// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/commandlineparser.hpp"
#include "../include/sequencesearcher.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
    CP::MatrixRowSearcher temp();

    CP::SearchMatrix data;
    std::vector<int> test = {1,2,3,1,1,4,5,6,7};
    data.push_back(std::move(test));
    CP::SequenceSearcher searcher(data);
    std::cout << "Searcher Created" << std::endl;
    CP::RowIndices indices = searcher.Search({1,2});
    indices = searcher.Search({ 0 });
    indices = searcher.Search({ 8 });
    indices = searcher.Search({ 7 });
    indices = searcher.Search({ 5,6,7 });
    indices = searcher.Search({ 1,1,4,5 });
    indices = searcher.Search({ 1,2,3,1,1,4,5,6,7 });
    indices = searcher.Search({ 1,1,4,6 });
    indices = searcher.Search({ 2,3,1,1,4,5,6,7 });
    return 0;
}