#include "../include/sequencesearcher.hpp"
#include <iostream>
namespace CP
{
    SequenceSearcher::SequenceSearcher(const SearchMatrix& inputData)
    :Searcher(inputData)
    {
        for(auto & row: inputData)
        {

            for(int i=0; i < static_cast<int>(row.size()); ++i)
            {
                SearchValue value =row[i];
                m_ValuePositionTable[value].push_back(i);
            }
        }
    }    
    RowIndices SequenceSearcher::Search(const std::vector<int>&sequence)
    {
        std::cout << "Searching" << std::endl;
        return RowIndices();
    }

    int SequenceSearcher::GetMaxPossibleLengthOfSequenceFromColumnIndex(int rowIndex,ColumnIndex colIndex)
    {

    }
}