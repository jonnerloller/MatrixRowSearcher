#include "../include/searcher.hpp"
#include <cassert>
namespace CP
{
    void NodePool::InitAndReserveMemory(std::size_t numNodesToReserve)
    {
        Clear();
        m_pool.reserve(numNodesToReserve);
    }

    void NodePool::Clear()
    {
        m_pool.resize(0);
    }

    SearchNode* NodePool::Allocate()
    {
        // If we resize our allactor, all our pointers will be invalidated.
        assert(m_pool.size() < m_pool.capacity());
        m_pool.push_back(SearchNode());
        return &m_pool.back();
    }

    SearchData::SearchData(const SearchMatrix&& inputData)
        :m_InputData(inputData)
    {
        //Hold's the root nodes
        m_PreProcessedData.reserve(inputData.size());

        size_t numRootNodes = inputData.size();
        size_t numNodesPerRow = inputData.size() > 0 ? inputData[0].size() : 0;

        //Right now our preprocessing stage uses on average 1/2 N^2 many nodes. Reserve extra in case.
        size_t numNodesToReservePerRow = numNodesPerRow * numNodesPerRow;
        size_t totalNumberOfNodesToReserve = numRootNodes * numNodesToReservePerRow + numRootNodes;

        m_MemoryPool.InitAndReserveMemory(totalNumberOfNodesToReserve);
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
            m_PreProcessedData.push_back(m_MemoryPool.Allocate());
            SearchNode* root = m_PreProcessedData.back();
            for (int i = 0; i < static_cast<int>(row.size()); ++i)
            {
                // Begin the chain.
                SearchNode* currentNode = root->InsertNode(row[i],m_MemoryPool);
                currentNode->m_indicesOfNodes.push_back(i);
                for (int j = i + 1; j < static_cast<int>(row.size()); ++j)
                {
                    SearchNode* tempNode = currentNode->InsertNode(row[j], m_MemoryPool,j);
                    currentNode = tempNode;
                }
            }
        }
    }

    SearchNode* SearchNode::InsertNode(SearchValue key,NodePool& memoryPool, int index)
    {
        auto it = m_children.find(key);
        SearchNode* currentNode = nullptr;

        // If we fail to find an existing node, we have to allocate a new node and insert it into the tree.
        if (it == m_children.end())
        {
            currentNode = memoryPool.Allocate();
            m_children[key] = currentNode;
        }
        else
        {
            currentNode = it->second;
        }
        
        // optimization: store the index of the node.
        if (currentNode && index != INVALID_INDEX)
        {
            m_indicesOfNodes.push_back(index);
        }

        return currentNode;
    }

    SearchNode* SearchNode::FindNode(SearchValue key)
    {
        auto it = m_children.find(key);
        if (it == m_children.end())
        {
            return nullptr;
        }
        return it->second;
    }

}