#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <vector>
#include <unordered_map>
#include <memory>
namespace CP
{
    using SearchValue = int;
    using RowData = std::vector<SearchValue>;
    using SearchMatrix = std::vector<RowData>;

    struct SearchNode
    {
        std::unordered_map<SearchValue, std::unique_ptr<SearchNode>> m_children;
        SearchNode* InsertNode(SearchValue key);
        SearchNode* FindNode(SearchValue key);
    };

    struct SearchData
    {
        SearchData(const SearchMatrix&& inputData);
        SearchData(const SearchData& rhs) = delete;
        SearchData(SearchData&& rhs) = delete;
        SearchData& operator = (const SearchData& rhs) = delete;
        SearchData& operator = (SearchData&& rhs) = delete;

        SearchMatrix m_InputData;
        std::vector<std::unique_ptr<SearchNode>> m_PreProcessedData;
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