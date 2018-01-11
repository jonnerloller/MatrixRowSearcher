#include "../include/sequencesearcher.hpp"
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
    RowIndices SequenceSearcher::Search()
    {

    }

    int SequenceSearcher::GetMaxPossibleLengthOfSequenceFromColumnIndex(int rowIndex,ColumnIndex colIndex)
    {

    }
}