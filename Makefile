SOURCEFILES = src/searchprogram.cpp src/matrixrowsearch.cpp src/commandlineoptions.cpp src/sequencesearcher.cpp src/existsearcher.cpp src/searcher.cpp src/unittests.cpp src/timer.cpp
#Will add tests later. Don't think i need to output intermediate .o files for such a small project.
TESTFILES = 

GCCFLAGS = -std=c++14 -Wall -Wextra
GCCOPTIMIZE = -O3


gccDebug:
	g++ -o searchprogram_gcc $(SOURCEFILES) $(TESTFILES) $(GCCFLAGS)

clangDebug:

clean:
	rm -f *.exe *.o *.obj