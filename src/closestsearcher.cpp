#include "../include/closestsearcher.hpp"
#include <algorithm>
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

    int ClosestSearcher::AnalyzePattern(int row, int col, const CP::RowData&sequence)
    {
        int numMatches = 0;

        int rowLength = static_cast<int>(m_SearchData->m_InputData[row].size());
        for (int i = col; (i < col + static_cast<int>(sequence.size())) && (i < rowLength); ++i)
        {
            if (m_SearchData->m_InputData[row][i] == sequence[i - col])++numMatches;
        }
        return numMatches;
    }
    
    int ClosestSearcher::SearchMatch(int row,SearchNode* node, const CP::RowData&sequence)
    {
        int numMatches = 0;
        if (sequence.size())
        {
            SearchNode* childNode = node->FindNode(sequence[0]);
            CP::RowData childSequence = CP::RowData(sequence.begin() + 1, sequence.end());
            
            // First number in our sequence is a match. Analyze the pattern to see how many matches there are!
            if (childNode != nullptr)
            {
                for (auto it : childNode->m_indicesOfNodes)
                {
                    numMatches = std::max(numMatches, AnalyzePattern(row, it, sequence));
                }
                if (numMatches == static_cast<int>(sequence.size())) return numMatches;
            }
            // We still have to check for shorter patterns.
            numMatches = std::max(numMatches,SearchMatch(row,node, childSequence));            
        }
        return numMatches;
    }

    int ClosestSearcher::SearchRowForClosestSequence(int row, const CP::RowData&sequence)
    {
        SearchNode* currentNode = m_SearchData->m_PreProcessedData[row];
        return SearchMatch(row,currentNode, sequence);
    }
}