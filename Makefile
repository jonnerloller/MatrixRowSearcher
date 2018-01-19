SOURCEFILES = src/searchprogram.cpp src/matrixrowsearch.cpp src/commandlineoptions.cpp src/sequencesearcher.cpp src/existsearcher.cpp src/searcher.cpp src/unittests.cpp src/closestsearcher.cpp src/timer.cpp

#Will add tests later. Don't think i need to output intermediate .o files for such a small project.
TESTFILES = 

GCCFLAGS = -std=c++14 -Wall -Wextra
GCCOPTIMIZE = -O3


gccDebug:
	g++ -o searchprogram_gcc $(SOURCEFILES) $(TESTFILES) $(GCCFLAGS)

gccOptimize:
	g++ -o searchprogram_gcc $(SOURCEFILES) $(TESTFILES) $(GCCFLAGS) $(GCCOPTIMIZE)

clean:
	rm -f *.exe *.o *.obj