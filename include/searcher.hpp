#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
namespace CP
{
    using SearchValue = int;
    using RowData = std::vector<SearchValue>;
    using SearchMatrix = std::vector<RowData>;
    using RowIndices = std::vector<int>;
    
    struct SearchNode;

    // Simple Allocator.
    class NodePool
    {
    public:
        NodePool() = default;
        ~NodePool() = default;
        NodePool(const NodePool& rhs) = delete;
        NodePool(NodePool&& rhs) = delete;
        NodePool& operator = (const NodePool& rhs) = delete;
        NodePool& operator = (NodePool&& rhs) = delete;

        void InitAndReserveMemory(size_t numNodesToReserve);
        void Clear();
        SearchNode* Allocate();
    private:
        std::vector<SearchNode> m_pool;
    };

    // We use Search Nodes to generate a tree of potential paths.
    // Each Node has the next possible node in the sequence as it's child.
    // E.g.
    // A-B-C-A-E
    // Root 
    //  |- A
    //     |-B
    //       |-C
    //         |-A
    //           |-E
    //     |-E
    //  |- B
    //  |- C
    //  |- E
    // Optimization: We store the indices of all instances of the value of thie search node
    // so that we can do a quick array lookup vs more node traversal.
    struct SearchNode
    {
        static const int INVALID_INDEX = -1;

        std::map<SearchValue, SearchNode*> m_children;
        std::vector<int> m_indicesOfNodes;

        SearchNode* InsertNode(SearchValue key, NodePool& pool, int index = INVALID_INDEX);
        SearchNode* FindNode(SearchValue key);
    };

    // Our Search Data. 
    // Holds the Unprocessed input[for optimization], and the preprocessed input , and the Custom allocator.
    // Each Row is treated separate. Essentially we work on just searching individual rows.
    struct SearchData
    {
        SearchData(const SearchMatrix&& inputData);
        SearchData(const SearchData& rhs) = delete;
        SearchData(SearchData&& rhs) = delete;
        SearchData& operator = (const SearchData& rhs) = delete;
        SearchData& operator = (SearchData&& rhs) = delete;
        ~SearchData() = default;

        SearchMatrix m_InputData;
        
        // Holds the root nodes to our rows.
        std::vector<SearchNode*> m_PreProcessedData;
        NodePool m_MemoryPool;
    };

    // interface of our Search function.
    // all other search functions inherit from this class
    class Searcher
    {
        public:
            Searcher(const std::shared_ptr<SearchData>& searchData):m_SearchData(searchData){}
            Searcher(const Searcher& rhs) = delete;
            Searcher(Searcher&& rhs) = delete;
            Searcher& operator = (const Searcher& rhs) = delete;
            Searcher& operator = (Searcher&& rhs) = delete;
            virtual ~Searcher() = default;

            // Performs a search, and returns the indices of rows that fulfill the criteria dictated by the Search Function.
            virtual RowIndices Search(const CP::RowData&sequence) = 0;
        protected:
            std::shared_ptr<SearchData> m_SearchData;
        private:
        
    };

}

#endif