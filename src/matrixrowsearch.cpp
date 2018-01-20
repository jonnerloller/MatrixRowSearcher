#include "../include/matrixrowsearch.hpp"
#include "../include/sequencesearcher.hpp"
#include "../include/existsearcher.hpp"
#include "../include/closestsearcher.hpp"
#include <utility>
#include <fstream>
#include <iterator>
#include <iostream>
namespace CP
{
    MatrixRowSearcher& MatrixRowSearcher::GetInstance()
    {
        static MatrixRowSearcher instance;
        return instance;
    }

    void MatrixRowSearcher::SetSearchData(const std::shared_ptr<SearchData>& searchData)
    {
        // Is called when we load a file. We have to reinitialize all our search functions
        // with the new data.

        m_Searches.clear();
        m_SearchData = searchData;
        AddSearchFunction("sequenceSearch", std::make_unique<CP::SequenceSearcher>(m_SearchData));
        AddSearchFunction("existSearch", std::make_unique<CP::ExistSearcher>(m_SearchData));
        AddSearchFunction("closestSearch", std::make_unique<CP::ClosestSearcher>(m_SearchData));
    }

    const std::shared_ptr<SearchData>& MatrixRowSearcher::GetSearchData()const
    {
        return m_SearchData;
    }

    void MatrixRowSearcher::PrintSequence(const RowData& sequence)
    {
        if (sequence.size())
        {
          std::cout << "[" << sequence[0];
          for (int i = 1; i < static_cast<int>(sequence.size()); ++i)
          {
              std::cout << "," << sequence[i];
          }
          std::cout << "]" << std::endl;
        }
    }

    void MatrixRowSearcher::PrintRowIndices(const RowIndices& indices)
    {
        if (indices.size())
        {
            std::cout << "[" << indices[0] << "]";
            for (int i = 1; i < static_cast<int>(indices.size()); ++i)
            {
                std::cout << ", [" << indices[i] << "]";
            }
            std::cout << std::endl;
        }
    }
    void MatrixRowSearcher::PrintRowAndRowIndices(const RowIndices& indices, const SearchMatrix& searchMatrix)
    {
        for (auto i : indices)
        {
            std::cout << "[" << i << "] : ";
            PrintSequence(searchMatrix[i]);
            std::cout << std::endl;
        }
    }

    RowIndices MatrixRowSearcher::Search(const std::string searchName, const RowData& sequence)
    {
        RowIndices result;
        // Make sure the search function exists. If not we won't return anything.
        auto it = m_Searches.find(searchName);
        if (it != m_Searches.end())
        {
            result = it->second->Search(sequence);
            if (m_Option == DISPLAY_ROW_INDEX_ONLY)
            {
                std::cout << "[" << searchName << "] completed with rows:" << std::endl;
                PrintRowIndices(result);
            }
            else if (m_Option == DISPLAY_ROW_INDEX_AND_DATA)
            {
                std::cout << "[" << searchName << "] completed with rows:" << std::endl;
                PrintRowAndRowIndices(result,m_SearchData->m_InputData);
            }
        }
        else
        {
            std::cerr << "Invalid Search function [" << searchName << "]" << std::endl;
        }
        return result;
    }

    void MatrixRowSearcher::AddSearchFunction(const std::string searchName, std::unique_ptr<Searcher>&& searchFunction)
    {
        m_Searches.emplace(std::make_pair(searchName, std::unique_ptr<Searcher>(std::move(searchFunction))));
    }

    void MatrixRowSearcher::SetDisplayOption(DisplayOptions option)
    {
        m_Option = option;
    }

    CP::MatrixRowSearcher::DisplayOptions MatrixRowSearcher::GetDisplayOption()const
    {
        return m_Option;
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
    
    void MatrixRowSearcher::LoadEncryptedFile(const std::string& str)
    {

    }
}