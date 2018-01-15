#ifndef SEQUENCESEARCHER_HPP
#define SEQUENCESEARCHER_HPP
#include "searcher.hpp"
#include <unordered_map>
#include <memory>
namespace CP
{


    class SequenceSearcher : public Searcher
    {
        public:
            SequenceSearcher(const std::shared_ptr<SearchData>& inputData) :Searcher(inputData) {}
        SequenceSearcher(const SequenceSearcher& rhs) = delete;
        SequenceSearcher(SequenceSearcher&& rhs) = delete;
        SequenceSearcher& operator = (const SequenceSearcher& rhs) = delete;
        SequenceSearcher& operator = (SequenceSearcher&& rhs) = delete;
        virtual ~SequenceSearcher() = default;
        virtual RowIndices Search(const std::vector<int>&sequence) override;
        protected:
        private:

        bool SearchRowForSequence(int row, const std::vector<int>&sequence);
    };
}

#endif