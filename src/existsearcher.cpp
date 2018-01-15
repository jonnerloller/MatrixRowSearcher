#include "../include/existsearcher.hpp"
namespace CP
{
    RowIndices ExistSearcher::Search(const std::vector<int>&sequence)
    {
        RowIndices rows;
        rows.reserve(m_SearchDataRef.m_InputDataRef.size());

        for (int row = 0; row < static_cast<int>(m_SearchDataRef.m_InputDataRef.size()); ++row)
        {
            // I can guarantee that the first node is not empty because there will be 1 root node 

            if (SearchRowForSequence(row, sequence))
                rows.push_back(row);
        }

        return rows;
    }

    bool ExistSearcher::SearchRowForSequence(int row, const std::vector<int>&sequence)
    {
        SearchNode* currentNode = m_SearchDataRef.m_PreProcessedData[row].get();
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