#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include <utility>
#include <fstream>
#include <iterator>
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
        if (it != m_Searches.end())
        {
            return it->second->Search(sequence);
        }
        return RowIndices();
    }

    void MatrixRowSearcher::Add(const std::string searchName, std::unique_ptr<Searcher>&& searchFunction)
    {
        m_Searches.emplace(std::make_pair(searchName, std::unique_ptr<Searcher>(std::move(searchFunction))));
    }
    void MatrixRowSearcher::LoadFile(const std::string& str)
    {
        std::ifstream file(str);
        std::istream_iterator<int> it(file);
        std::istream_iterator<int> eof;
        CP::RowData data;
        std::copy(it, eof, std::back_inserter(data));
        CP::SearchMatrix searchMatrix;
        // First 2 arguments are Width and Height
        if (data.size() > 2)
        {
            int width = data[0];
            int height = data[1];

            // We read all the matrix data together.
            // the first row starts after the first 2 arguments
            // we need to offset each row and copy the data.
            int rowOffset = 2;
            searchMatrix.resize(height);
            for (int i = 0; i < height; ++i)
            {
                searchMatrix[i].resize(width);
                std::copy(data.begin() + rowOffset, data.begin() + rowOffset + width, searchMatrix[i].begin());
                rowOffset += width;
            }
            std::shared_ptr<CP::SearchData> searchData = std::make_shared<CP::SearchData>(std::move(searchMatrix));
            GetInstance().SetSearchData(searchData);
        }
    }
}