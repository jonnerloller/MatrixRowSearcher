#ifndef EXISTSEARCHER_HPP
#define EXISTSEARCHER_HPP
#include "searcher.hpp"
#include <unordered_map>
#include <memory>
namespace CP
{
    class ExistSearcher : public Searcher
    {
    public:
        ExistSearcher(const SearchData& inputData) :Searcher(inputData) {}
        ExistSearcher(const ExistSearcher& rhs) = delete;
        ExistSearcher(ExistSearcher&& rhs) = delete;
        ExistSearcher& operator = (const ExistSearcher& rhs) = delete;
        ExistSearcher& operator = (ExistSearcher&& rhs) = delete;
        virtual ~ExistSearcher() = default;
        virtual RowIndices Search(const std::vector<int>&sequence) override;
    protected:
    private:

        bool SearchRowForSequence(int row, const std::vector<int>&sequence);
    };
}

#endif