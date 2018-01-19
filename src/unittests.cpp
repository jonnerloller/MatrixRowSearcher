#include "../include/unittests.hpp"
#include "../include/matrixrowsearch.hpp"
#include "../include/timer.hpp"
#include <cassert>
#include <iostream>

namespace CP
{
    static void RunTest(const std::string& searchName, CP::RowData&& sequence, CP::RowIndices&& expectedResult, bool displayTestSequence = true)
    {
        if (displayTestSequence)
        {
            std::cout << "Running test [" << searchName << "] with sequence [";
            if (sequence.size())
            {
                std::cout << sequence[0];
            }
            for (int i = 1; i < static_cast<int>(sequence.size()); ++i)
            {
                std::cout << "," << sequence[i];
            }
            std::cout << "]" << std::endl;
        }
        

        CP::MatrixRowSearcher& matrixRowSearcher = CP::MatrixRowSearcher::GetInstance();
        CP::RowIndices indices = matrixRowSearcher.Search(searchName, sequence);
        assert(expectedResult.size() == indices.size());
        for (int i = 0; i < static_cast<int>(expectedResult.size()); ++i)
        {
            if (i < static_cast<int>(expectedResult.size()))
            {
                // These 2 have to be identical
                assert(expectedResult[i] == indices[i]);
            }
        }
    }
    void RunSequenceSearchUnitTests()
    {
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");
        std::cout << "Begin running [Sequence Search] tests" <<std::endl;
       
        RunTest("sequenceSearch", { 0 }, { 4,5});
        RunTest("sequenceSearch", { 1 }, { 0,1,2,4,5 });
        RunTest("sequenceSearch", { 2 }, { 0,1,2,4,5 });
        RunTest("sequenceSearch", { 3 }, {0,1,2});
        RunTest("sequenceSearch", { 4 }, {0,1,5});
        RunTest("sequenceSearch", { 5 }, {0,1});
        RunTest("sequenceSearch", { 6 }, {0,1,5});
        RunTest("sequenceSearch", { 1,2 }, {0,2});
        RunTest("sequenceSearch", { 2,3 }, {0});
        RunTest("sequenceSearch", { 3,4 }, { 0 });
        RunTest("sequenceSearch", { 4,3 }, { 1 });
        RunTest("sequenceSearch", { 2,1 }, {1,2,5});
        RunTest("sequenceSearch", { 1,1 }, {2});
        RunTest("sequenceSearch", { 5,4 }, { 1 });
        /*
        1 2 3 4 5 6
        6 5 4 3 2 1
        1 1 1 2 1 3
        11 305 468 213 446 102
        0 1 0 2 9 7
        6 0 4 2 2 1
        */
        std::cout << "[Sequence Search] tests complete" <<std::endl;
    }

    void RunExistSearchUnitTests()
    {
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");

        std::cout << "Begin running [Exist Search] tests" <<std::endl;
        RunTest("existSearch", { 0 }, { 4 ,5});
        RunTest("existSearch", { 10 }, { });
        RunTest("existSearch", { 2 }, { 0,1,2,4 ,5});
        RunTest("existSearch", { 3 }, { 0,1,2 });
        RunTest("existSearch", { 4 }, { 0,1,5});
        RunTest("existSearch", { 5 }, { 0,1 });
        RunTest("existSearch", { 6 }, { 0,1,5});
        RunTest("existSearch", { 1,2 }, { 0,1,2,4,5});
        RunTest("existSearch", { 3,1 }, { 0,1,2 });
        /*
        1 2 3 4 5 6
        6 5 4 3 2 1
        1 1 1 2 1 3
        11 305 468 213 446 102
        0 1 0 2 9 7
        6 0 4 2 2 1
        */
        std::cout << "[Exist Search] tests complete" <<std::endl;
    }

    void RunClosestSearchUnitTests()
    {
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");

        std::cout << "Begin running [Exist Search] tests" << std::endl;
        RunTest("closestSearch", {1,0,3,7,5}, { 0 });
        RunTest("closestSearch", { 1,20,1,5 }, { 2 });
        RunTest("closestSearch", { 468,0,7,25 }, { 3 });
        RunTest("closestSearch", { 1,2,1,4 }, { 0 });
        RunTest("closestSearch", { 5,0,4,2 }, { 5 });
        /*
        1 2 3 4 5 6
        6 5 4 3 2 1
        1 1 1 2 1 3
        11 305 468 213 446 102
        0 1 0 2 9 7
        6 0 4 2 2 1
        */

        //
        //
        // 5 0 4 2 
        //
        //
        //
        //
        //
        std::cout << "[Exist Search] tests complete" << std::endl;
    }

    void RunLargeTests()
    {
        std::cout << "Loading and processing Data" << std::endl;
        CP::MatrixRowSearcher::LoadFile("data/large.txt");
        std::cout << "Data processed!" << std::endl;

        std::cout << "Begin running [Large] tests" << std::endl;
        Timer timer;
        timer.StartTimer();
        int numIterations = 1000;
        for (int i = 0; i < numIterations; ++i)
        {
            RunTest("closestSearch", { 1,0,0,0,0,0,2500,313 }, { 0 },false);
        }
        timer.StopTimer();
        std::cout << "Tests took " << timer.GetNanoseconds().count() << "ns" << std::endl;
        std::cout << "Average time per iteration " << timer.GetNanoseconds().count() / numIterations << "ns" << std::endl;

        timer.StartTimer();
        numIterations = 2500;
        for (int i = 0; i < numIterations; ++i)
        {
            RunTest("sequenceSearch", { 1,numIterations,0,1,numIterations + 1,0,313 }, numIterations == 2498 ? CP::RowIndices{0} : CP::RowIndices(), false);
        }
        timer.StopTimer();
        std::cout << "Tests took " << timer.GetNanoseconds().count() << "ns" << std::endl;
        std::cout << "Average time per iteration " << timer.GetNanoseconds().count() / numIterations << "ns" << std::endl;

    }
}