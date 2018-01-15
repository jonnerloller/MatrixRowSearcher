#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include <utility>
namespace CP
{
    MatrixRowSearcher& MatrixRowSearcher::GetInstance()
    {
        static MatrixRowSearcher instance;
        return instance;
    }

    void MatrixRowSearcher::SetSearchData(const std::shared_ptr<SearchData>& searchData)
    {
        m_Searches.clear();
        m_SearchData = searchData;
        Add("sequenceSearch", std::make_unique<CP::SequenceSearcher>(m_SearchData));
        Add("existSearch", std::make_unique<CP::ExistSearcher>(m_SearchData));
    }

    const std::shared_ptr<SearchData>& MatrixRowSearcher::GetSearchData()const
    {
        return m_SearchData;
    }

    RowIndices MatrixRowSearcher::Search(const std::string searchName, const RowData& sequence)
    {
        auto it = m_Searches.find(searchName);
        if(it != m_Searches.end())
        {
            return it->second->Search(sequence);
        }
        return RowIndices();
    }

    void MatrixRowSearcher::Add(const std::string searchName, std::unique_ptr<Searcher>&& searchFunction)
    {
        m_Searches.emplace(std::make_pair(searchName, std::unique_ptr<Searcher>(std::move(searchFunction))));
    }
}