#ifndef SEQUENCESEARCH_HPP
#define SEQUENCESEARCH_HPP
#include "searcher.hpp"
#include <unordered_map>
#include <memory>
namespace CP
{
    struct SearchNode
    {
        std::unordered_map<SearchValue,std::unique_ptr<SearchNode>> m_children;
        SearchNode* InsertNode(SearchValue key);
        SearchNode* FindNode(SearchValue key);
    };

    class SequenceSearcher : public Searcher
    {
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

        bool SearchRowForSequence(int row, const std::vector<int>&sequence);

        std::vector<std::unique_ptr<SearchNode>> m_roots;
    };
}

#endif