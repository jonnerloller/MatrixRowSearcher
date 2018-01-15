#include "../include/sequencesearcher.hpp"
#include <iostream>
#include <iterator>
namespace CP
{
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

    SequenceSearcher::SequenceSearcher(const SearchMatrix& inputData)
    :Searcher(inputData)
    {
        m_roots.reserve(inputData.size());
        for(auto & row: inputData)
        {
            // I know this is a N^2 loop but we'll just do it for now...
            // There are probably a few optimizations that can be done here
            // Algo is simple.
            // Build each possible sequence using hash tables.
            // Originally was just going to be a Hash table with a vector of nodes, but
            // node traversal in the case of a b a c a d a e a f a g a h a i becomes increasingly high,
            // so if we can make the node traversal O(1), it might be worth the memory tradeoff?
            // so basically we are just having hash tables of hash tables of hash tables.
            m_roots.push_back(std::make_unique<SearchNode>());
            SearchNode* root = m_roots.back().get();
            for(int i=0; i < static_cast<int>(row.size()); ++i)
            {
                // Begin the chain.
                SearchNode* currentNode = root->InsertNode(row[i]);
                for(int j=i+1; j < static_cast<int>(row.size()); ++j)
                {
                    SearchNode* tempNode = currentNode->InsertNode(row[j]);
                    currentNode = tempNode;
                }   
            }
        }
    }    
    RowIndices SequenceSearcher::Search(const std::vector<int>&sequence)
    {
        RowIndices rows;
        rows.reserve(m_roots.size());
        
        for (int row = 0; row < static_cast<int>(m_roots.size()); ++row)
        {
            // I can guarantee that the first node is not empty because there will be 1 root node 
            
            if (SearchRowForSequence(row, sequence)) 
                rows.push_back(row);
        }

        return rows;
    }

    bool SequenceSearcher::SearchRowForSequence(int row, const std::vector<int>&sequence)
    {
        SearchNode* currentNode = m_roots[row].get();
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