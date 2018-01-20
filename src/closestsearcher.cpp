#include "../include/closestsearcher.hpp"
#include <algorithm>
namespace CP
{
    RowIndices ClosestSearcher::Search(const CP::RowData&sequence)
    {
        RowIndices rows;

        //unlike the other search algorithms, we cannot early terminate here
        //because closest match works that way.

        rows.reserve(m_SearchData->m_InputData.size());

        int mostMatches= -1;
        int greatestRow = -1;
        for (int row = 0; row < static_cast<int>(m_SearchData->m_InputData.size()); ++row)
        {
            int numMatches = SearchRowForClosestSequence(row, sequence);
            // store the row with the greatest number of matches.
            if (numMatches > mostMatches)
            {
                mostMatches = numMatches;
                greatestRow = row;
            }
        }
        rows.push_back(greatestRow);

        return rows;
    }

    // Find the number of matches in the sequence window.
    // e.g.
    // col = 0
    // [A X C]
    // [A B C A E F]
    // [1 0 1] = 2 matches
    //
    // col = 3      
    //       [A X C]
    // [A B C A E F]
    // [1 0 1] = 2 matches
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
    
    // We first search for the first number in the sequence, and count the number of matching
    // numbers in the sequence from the first number using AnalyzePattern
    // However, we cannot assume that matching the first number is the best, so 
    // we have to analyze smaller patterns as well.
    // e.g
    // A B C D E F [input data]
    // B D E F [sequence]
    // If we just assumed that B matching generated the "closest match"
    // then we would have only 1 match
    // but if we analyzed a smaller sequence, i.e DEF. 
    // we would have 3 matches.
    int ClosestSearcher::SearchMatch(int row,SearchNode* node, const CP::RowData&sequence)
    {
        int numMatches = 0;
        if (sequence.size())
        {
            SearchNode* childNode = node->FindNode(sequence[0]);
            // Generate a smaller child sequence.
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

            numMatches = std::max(numMatches,SearchMatch(row,node, childSequence));            
        }
        return numMatches;
    }

    // Search Row For Closest Sequence.
    int ClosestSearcher::SearchRowForClosestSequence(int row, const CP::RowData&sequence)
    {
        SearchNode* currentNode = m_SearchData->m_PreProcessedData[row];
        return SearchMatch(row,currentNode, sequence);
    }
}