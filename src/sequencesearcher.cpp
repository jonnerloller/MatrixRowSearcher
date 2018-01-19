#include "../include/sequencesearcher.hpp"
#include <iostream>
#include <iterator>
namespace CP
{  
    RowIndices SequenceSearcher::Search(const CP::RowData&sequence)
    {
        RowIndices rows;
        if (m_SearchData->m_InputData.size() && sequence.size() > m_SearchData->m_InputData[0].size())
        return rows;
        rows.reserve(m_SearchData->m_InputData.size());
        
        for (int row = 0; row < static_cast<int>(m_SearchData->m_InputData.size()); ++row)
        {
            // I can guarantee that the first node is not empty because there will be 1 root node 
            
            if (SearchRowForSequence(row, sequence)) 
                rows.push_back(row);
        }

        return rows;
    }

    bool SequenceSearcher::SearchRowForSequence(int row, const CP::RowData&sequence)
    {
        SearchNode* currentNode = m_SearchData->m_PreProcessedData[row];
        // iterate through nodes. If there is a next node, the sequence exists.
        // if we fail to find a next node, the sequence does not exist.
        for (int num : sequence)
        {
            currentNode = currentNode->FindNode(num);
            if (currentNode == nullptr) return false;
        }
        return true;
    }
}