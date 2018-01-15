#ifndef MATRIXROWSEARCH_HPP
#define MATRIXROWSEARCH_HPP
#include "searcher.hpp"
#include <map>
#include <string>
namespace CP
{
    // This should be the Program itself
    // The main program just instantiates this class and runs it.
    class MatrixRowSearcher
    {
        public:

            static MatrixRowSearcher& GetInstance();

            RowIndices Search(const std::string searchName, const RowData& sequence);
            void Add(const std::string searchName, std::unique_ptr<Searcher>&& searchFunction);
            void SetSearchData(const std::shared_ptr<SearchData>& searchData);
            const std::shared_ptr<SearchData>& GetSearchData()const;
        private:
            MatrixRowSearcher() = default;
            MatrixRowSearcher(const MatrixRowSearcher& rhs) = delete;
            MatrixRowSearcher(MatrixRowSearcher&& rhs) = default;
            MatrixRowSearcher& operator = (const MatrixRowSearcher& rhs) = delete;
            MatrixRowSearcher& operator = (MatrixRowSearcher&& rhs) = default;
            virtual ~MatrixRowSearcher() = default;
            std::map<std::string, std::unique_ptr<Searcher>> m_Searches;
            std::shared_ptr<SearchData> m_SearchData;
    };
}

#endif