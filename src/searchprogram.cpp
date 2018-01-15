// SearchProgram.cpp
#include "../include/matrixrowsearch.hpp"
#include "../include/commandlineparser.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
    CP::MatrixRowSearcher temp();

    CP::SearchMatrix data;
    std::vector<int> test = {1,2,3,1,1,4,5,6,7};
    data.push_back(std::move(test));
    CP::SearchData searchData(data);
    CP::SequenceSearcher sequenceSearcher(searchData);
    CP::ExistSearcher existSearcher(searchData);
    std::cout << "Searcher Created" << std::endl;
    CP::RowIndices indices = sequenceSearcher.Search({1,2});
    indices = sequenceSearcher.Search({ 0 });
    indices = sequenceSearcher.Search({ 8 });
    indices = sequenceSearcher.Search({ 7 });
    indices = sequenceSearcher.Search({ 5,6,7 });
    indices = sequenceSearcher.Search({ 1,1,4,5 });
    indices = sequenceSearcher.Search({ 1,2,3,1,1,4,5,6,7 });
    indices = sequenceSearcher.Search({ 1,1,4,6 });
    indices = sequenceSearcher.Search({ 2,3,1,1,4,5,6,7 });

    indices = existSearcher.Search({ 0 });
    indices = existSearcher.Search({ 2,7 });
    indices = existSearcher.Search({ 1,6 });
    indices = existSearcher.Search({ 2,3,8 });
    indices = existSearcher.Search({ 4,4,4,4,4,1 });
    
    return 0;
}