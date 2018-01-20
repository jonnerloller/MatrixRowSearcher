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
            std::cout << "Running test [" << searchName << "] with sequence ";
            MatrixRowSearcher::PrintSequence(sequence);
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
        CP::MatrixRowSearcher::DisplayOptions currentOption = CP::MatrixRowSearcher::GetInstance().GetDisplayOption();
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(MatrixRowSearcher::DISPLAY_NONE);
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");
        std::cout << "Begin running [Sequence Search] tests" <<std::endl;
       
        RunTest("sequenceSearch", { 0 }, { 4,5}, false);
        RunTest("sequenceSearch", { 1 }, { 0,1,2,4,5 }, false);
        RunTest("sequenceSearch", { 2 }, { 0,1,2,4,5 }, false);
        RunTest("sequenceSearch", { 3 }, {0,1,2}, false);
        RunTest("sequenceSearch", { 4 }, {0,1,5}, false);
        RunTest("sequenceSearch", { 5 }, {0,1}, false);
        RunTest("sequenceSearch", { 6 }, {0,1,5}, false);
        RunTest("sequenceSearch", { 1,2 }, {0,2}, false);
        RunTest("sequenceSearch", { 2,3 }, {0}, false);
        RunTest("sequenceSearch", { 3,4 }, { 0 }, false);
        RunTest("sequenceSearch", { 4,3 }, { 1 }, false);
        RunTest("sequenceSearch", { 2,1 }, {1,2,5}, false);
        RunTest("sequenceSearch", { 1,1 }, {2}, false);
        RunTest("sequenceSearch", { 5,4 }, { 1 }, false);

        std::cout << "[Sequence Search] tests complete" <<std::endl;
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(currentOption);
    }

    void RunExistSearchUnitTests()
    {
        CP::MatrixRowSearcher::DisplayOptions currentOption = CP::MatrixRowSearcher::GetInstance().GetDisplayOption();
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(MatrixRowSearcher::DISPLAY_NONE);
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");

        std::cout << "Begin running [Exist Search] tests" <<std::endl;
        RunTest("existSearch", { 0 }, { 4 ,5}, false);
        RunTest("existSearch", { 10 }, { }, false);
        RunTest("existSearch", { 2 }, { 0,1,2,4 ,5}, false);
        RunTest("existSearch", { 3 }, { 0,1,2 }, false);
        RunTest("existSearch", { 4 }, { 0,1,5}, false);
        RunTest("existSearch", { 5 }, { 0,1 }, false);
        RunTest("existSearch", { 6 }, { 0,1,5}, false);
        RunTest("existSearch", { 1,2 }, { 0,1,2,4,5}, false);
        RunTest("existSearch", { 3,1 }, { 0,1,2 }, false);

        std::cout << "[Exist Search] tests complete" <<std::endl;
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(currentOption);
    }

    void RunClosestSearchUnitTests()
    {
        CP::MatrixRowSearcher::DisplayOptions currentOption = CP::MatrixRowSearcher::GetInstance().GetDisplayOption();
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(MatrixRowSearcher::DISPLAY_NONE);
        CP::MatrixRowSearcher::LoadFile("data/simple.txt");

        std::cout << "Begin running [Exist Search] tests" << std::endl;
        RunTest("closestSearch", {1,0,3,7,5}, { 0 }, false);
        RunTest("closestSearch", { 1,20,1,5 }, { 2 }, false);
        RunTest("closestSearch", { 468,0,7,25 }, { 3 }, false);
        RunTest("closestSearch", { 1,2,1,4 }, { 0 }, false);
        RunTest("closestSearch", { 5,0,4,2 }, { 5 }, false);

        std::cout << "[Exist Search] tests complete" << std::endl;
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(currentOption);
    }

    void RunLargeTests()
    {
        CP::MatrixRowSearcher::DisplayOptions currentOption = CP::MatrixRowSearcher::GetInstance().GetDisplayOption();
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(MatrixRowSearcher::DISPLAY_NONE);
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
        CP::MatrixRowSearcher::GetInstance().SetDisplayOption(currentOption);
    }
}