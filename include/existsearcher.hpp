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
        ExistSearcher(const std::shared_ptr<SearchData>& inputData) :Searcher(inputData) {}
        ExistSearcher(const ExistSearcher& rhs) = delete;
        ExistSearcher(ExistSearcher&& rhs) = delete;
        ExistSearcher& operator = (const ExistSearcher& rhs) = delete;
        ExistSearcher& operator = (ExistSearcher&& rhs) = delete;
        virtual ~ExistSearcher() = default;
        virtual RowIndices Search(const CP::RowData&sequence) override;
    protected:
    private:

        bool SearchRowForSequence(int row, const CP::RowData&sequence);
    };
}

#endif