#ifndef SEQUENCESEARCH_HPP
#define SEQUENCESEARCH_HPP
#include "searcher.hpp"
#include <unordered_map>
namespace CP
{
    class SequenceSearcher : public Searcher
    {
        private:
        using ColumnIndex = int;
        using ValuePositions = std::vector<ColumnIndex>;
        using HashTable = std::unordered_map<SearchValue,ValuePositions>;
        public:
        SequenceSearcher(const SearchMatrix& inputData);
        SequenceSearcher(const SequenceSearcher& rhs) = delete;
        SequenceSearcher(SequenceSearcher&& rhs) = delete;
        SequenceSearcher& operator = (const SequenceSearcher& rhs) = delete;
        SequenceSearcher& operator = (SequenceSearcher&& rhs) = delete;
        virtual ~SequenceSearcher() = default;
        virtual RowIndices Search(const std::vector<int>&sequence) override;
        protected:
        private:

        int GetMaxPossibleLengthOfSequenceFromColumnIndex(int rowIndex,ColumnIndex colIndex);


        HashTable m_ValuePositionTable;
    };
}

#endif