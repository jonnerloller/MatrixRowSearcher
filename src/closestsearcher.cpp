#include "../include/closestsearcher.hpp"
namespace CP
{
    RowIndices ClosestSearcher::Search(const CP::RowData&sequence)
    {
        RowIndices rows;
        rows.reserve(m_SearchData->m_InputData.size());

        int mostMatches= -1;
        int greatestRow = -1;
        for (int row = 0; row < static_cast<int>(m_SearchData->m_InputData.size()); ++row)
        {
            // I can guarantee that the first node is not empty because there will be 1 root node 

            int numMatches = SearchRowForClosestSequence(row, sequence);
            if (numMatches > mostMatches)
            {
                mostMatches = numMatches;
                greatestRow = row;
            }
        }
        rows.push_back(greatestRow);

        return rows;
    }
    //
    int SearchMatch(SearchNode* node, const CP::RowData&sequence)
    {
        int numMatches = 0;
        if (sequence.size())
        {
            SearchNode* childNode = node->FindNode(sequence[0]);
            CP::RowData childSequence = CP::RowData(sequence.begin() + 1, sequence.end());
            if (childNode != nullptr)
            {
                numMatches = 1 + SearchMatch(childNode, childSequence);
                if (numMatches == sequence.size()) return numMatches;
            }
            for (const auto &it : node->m_children)
            {
                numMatches = SearchMatch(it.second.get(), childSequence);
                if (numMatches == sequence.size()) return numMatches;
            }
            
        }
        return numMatches;
    }

    int ClosestSearcher::SearchRowForClosestSequence(int row, const CP::RowData&sequence)
    {
        SearchNode* currentNode = m_SearchData->m_PreProcessedData[row].get();
        return SearchMatch(currentNode, sequence);
    }
}