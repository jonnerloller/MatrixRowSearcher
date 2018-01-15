#include "../include/searcher.hpp"
namespace CP
{
    SearchData::SearchData(const SearchMatrix& inputData)
        :m_InputDataRef(inputData)
    {
        m_PreProcessedData.reserve(inputData.size());
        for (auto & row : inputData)
        {
            // I know this is a N^2 loop but we'll just do it for now...
            // There are probably a few optimizations that can be done here
            // Algo is simple.
            // Build each possible sequence using hash tables.
            // Originally was just going to be a Hash table with a vector of nodes, but
            // node traversal in the case of a b a c a d a e a f a g a h a i becomes increasingly high,
            // so if we can make the node traversal O(1), it might be worth the memory tradeoff?
            // so basically we are just having hash tables of hash tables of hash tables.
            m_PreProcessedData.push_back(std::make_unique<SearchNode>());
            SearchNode* root = m_PreProcessedData.back().get();
            for (int i = 0; i < static_cast<int>(row.size()); ++i)
            {
                // Begin the chain.
                SearchNode* currentNode = root->InsertNode(row[i]);
                for (int j = i + 1; j < static_cast<int>(row.size()); ++j)
                {
                    SearchNode* tempNode = currentNode->InsertNode(row[j]);
                    currentNode = tempNode;
                }
            }
        }
    }
    SearchNode* SearchNode::InsertNode(SearchValue key)
    {
        auto it = m_children.find(key);
        if (it == m_children.end())
        {
            std::unique_ptr<SearchNode> node = std::make_unique<SearchNode>();
            SearchNode* currentNode = node.get();
            m_children[key] = std::move(node);
            return currentNode;
        }

        return it->second.get();
    }
    SearchNode* SearchNode::FindNode(SearchValue key)
    {
        auto it = m_children.find(key);
        if (it == m_children.end())
        {
            return nullptr;
        }
        return it->second.get();
    }

}