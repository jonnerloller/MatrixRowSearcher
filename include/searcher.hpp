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
    
    struct SearchNode;
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

    struct SearchNode
    {
        static const int INVALID_INDEX = -1;
        std::map<SearchValue, SearchNode*> m_children;
        std::vector<int> m_indicesOfNodes;

        SearchNode* InsertNode(SearchValue key, NodePool& pool, int index = INVALID_INDEX);
        SearchNode* FindNode(SearchValue key);
    };

    struct SearchData
    {
        SearchData(const SearchMatrix&& inputData);
        SearchData(const SearchData& rhs) = delete;
        SearchData(SearchData&& rhs) = delete;
        SearchData& operator = (const SearchData& rhs) = delete;
        SearchData& operator = (SearchData&& rhs) = delete;
        ~SearchData() = default;

        SearchMatrix m_InputData;
        std::vector<SearchNode*> m_PreProcessedData;
        NodePool m_MemoryPool;
    };

    using RowIndices = std::vector<int>;
    class Searcher
    {
        public:
            Searcher(const std::shared_ptr<SearchData>& searchData):m_SearchData(searchData){}
            Searcher(const Searcher& rhs) = delete;
            Searcher(Searcher&& rhs) = delete;
            Searcher& operator = (const Searcher& rhs) = delete;
            Searcher& operator = (Searcher&& rhs) = delete;
            virtual ~Searcher() = default;
            virtual RowIndices Search(const CP::RowData&sequence) = 0;
        protected:
            std::shared_ptr<SearchData> m_SearchData;
        private:
        
    };

}

#endif