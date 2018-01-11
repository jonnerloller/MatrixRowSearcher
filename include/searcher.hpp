#ifndef SEARCH_HPP
#define SEARCH_HPP
#include <vector>
namespace CP
{
    using SearchValue = int;
    using RowData = std::vector<int>;
    using SearchMatrix = std::vector<RowData>;

    using RowIndices = std::vector<int>;
    class Searcher
    {
        public:
        Searcher(const SearchMatrix& inputData):m_InputDataRef(inputData){}
        Searcher(const Searcher& rhs) = delete;
        Searcher(Searcher&& rhs) = delete;
        Searcher& operator = (const Searcher& rhs) = delete;
        Searcher& operator = (Searcher&& rhs) = delete;
        virtual ~Searcher() = default;
        virtual RowIndices Search(const std::vector<int>&sequence) = 0;
        protected:
        private:
        const SearchMatrix& m_InputDataRef;
    };

}

#endif