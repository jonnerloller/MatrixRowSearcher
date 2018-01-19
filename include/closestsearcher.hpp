#ifndef CLOSESTSEARCHER_HPP
#define CLOSESTSEARCHER_HPP
#include "searcher.hpp"
#include <unordered_map>
#include <memory>
namespace CP
{
    class ClosestSearcher : public Searcher
    {
    public:
        ClosestSearcher(const std::shared_ptr<SearchData>& inputData) :Searcher(inputData) {}
        ClosestSearcher(const ClosestSearcher& rhs) = delete;
        ClosestSearcher(ClosestSearcher&& rhs) = delete;
        ClosestSearcher& operator = (const ClosestSearcher& rhs) = delete;
        ClosestSearcher& operator = (ClosestSearcher&& rhs) = delete;
        virtual ~ClosestSearcher() = default;
        virtual RowIndices Search(const CP::RowData&sequence) override;
    protected:
    private:

        int SearchRowForClosestSequence(int row, const CP::RowData&sequence);
        int SearchMatch(int row,SearchNode* node, const CP::RowData&sequence);
        int AnalyzePattern(int row, int col, const CP::RowData&sequence);
    };
}
#endif