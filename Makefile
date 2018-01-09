SOURCEFILES = src/SearchProgram.cpp src/commandlineparser.cpp src/matrixrowsearch.cpp
#Will add tests later. Don't think i need to output intermediate .o files for such a small project.
TESTFILES = 
GCCFLAGS = -std=c++17 -Wall -Wextra
GCCOPTIMIZE = -O3


gccDebug:
	gcc -o SearchProgram_gcc.exe $(SOURCEFILES) $(TESTFILES) $(GCCFLAGS)

clangDebug:

clean:
	rm -f *.exe *.o *.obj