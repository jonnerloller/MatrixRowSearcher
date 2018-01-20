#include "../include/existsearcher.hpp"
namespace CP
{
    RowIndices ExistSearcher::Search(const CP::RowData&sequence)
    {
        RowIndices rows;
        
        //early termination.
        if (m_SearchData->m_InputData.size() && sequence.size() > m_SearchData->m_InputData[0].size())
            return rows;

        rows.reserve(m_SearchData->m_InputData.size());

        for (int row = 0; row < static_cast<int>(m_SearchData->m_InputData.size()); ++row)
        {
            if (SearchRowForSequence(row, sequence))
                rows.push_back(row);
        }

        return rows;
    }

    bool ExistSearcher::SearchRowForSequence(int row, const CP::RowData&sequence)
    {
        SearchNode* currentNode = m_SearchData->m_PreProcessedData[row];
        // For this search, we just need to know if All numbers in the sequence exist in our data.
        // So we just need to check the root, no need to traverse.
        for (int num : sequence)
        {
            SearchNode* node = currentNode->FindNode(num);
            if (node == nullptr) return false;
        }
        return true;
    }
}