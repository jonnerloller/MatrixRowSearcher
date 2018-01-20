#ifndef MATRIXROWSEARCH_HPP
#define MATRIXROWSEARCH_HPP
#include "searcher.hpp"
#include <map>
#include <string>
namespace CP
{
    // Basically the "application" itself, this class handles most of the
    // program logic called by the command line parser.
    class MatrixRowSearcher
    {
        public:
            enum DisplayOptions
            {
                DISPLAY_ROW_INDEX_ONLY = 0,
                DISPLAY_ROW_INDEX_AND_DATA,
                DISPLAY_NONE,
            };

            static MatrixRowSearcher& GetInstance();

            RowIndices Search(const std::string searchName, const RowData& sequence);
            void AddSearchFunction(const std::string searchName, std::unique_ptr<Searcher>&& searchFunction);
            void SetSearchData(const std::shared_ptr<SearchData>& searchData);
            void SetDisplayOption(DisplayOptions option);
            DisplayOptions GetDisplayOption()const;
            const std::shared_ptr<SearchData>& GetSearchData()const;

            static void ProcessFileData(const std::vector<int>& data);
            static void LoadFile(const std::string& inputFileName);
            static void LoadEncryptedFile(const std::string& inputFileName, int key);
            static void EncryptFile(const std::string& inputFileName,const std::string& outputFileName, int key);
            static void PrintSequence(const RowData& sequence);
            static void PrintRowIndices(const RowIndices& indices);
            static void PrintRowAndRowIndices(const RowIndices& indices, const SearchMatrix& searchMatrix);
        private:
            MatrixRowSearcher() = default;
            MatrixRowSearcher(const MatrixRowSearcher& rhs) = delete;
            MatrixRowSearcher(MatrixRowSearcher&& rhs) = default;
            MatrixRowSearcher& operator = (const MatrixRowSearcher& rhs) = delete;
            MatrixRowSearcher& operator = (MatrixRowSearcher&& rhs) = default;
            virtual ~MatrixRowSearcher() = default;
            std::map<std::string, std::unique_ptr<Searcher>> m_Searches;
            std::shared_ptr<SearchData> m_SearchData;
            DisplayOptions m_Option;

    };
}

#endif