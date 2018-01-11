#ifndef MATRIXROWSEARCH_HPP
#define MATRIXROWSEARCH_HPP

namespace CP
{
    // This should be the Program itself
    // The main program just instantiates this class and runs it.
    class MatrixRowSearcher
    {
        public:

        

        MatrixRowSearcher() = default;
        MatrixRowSearcher(const MatrixRowSearcher& rhs) = delete;
        MatrixRowSearcher(MatrixRowSearcher&& rhs) = default;
        MatrixRowSearcher& operator = (const MatrixRowSearcher& rhs) = delete;
        MatrixRowSearcher& operator = (MatrixRowSearcher&& rhs) = default;
        virtual ~MatrixRowSearcher() = default;
        private:
    };
}

#endif