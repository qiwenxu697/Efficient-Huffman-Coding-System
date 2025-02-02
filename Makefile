CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: compress uncompress

compress: compress.o HCTree.o Helper.o
	$(CXX) $(CXXFLAGS) -o compress compress.o HCTree.o Helper.o

uncompress: uncompress.o HCTree.o Helper.o
	$(CXX) $(CXXFLAGS) -o uncompress uncompress.o HCTree.o Helper.o

compress.o: compress.cpp HCTree.hpp Helper.hpp
	$(CXX) $(CXXFLAGS) -c compress.cpp

uncompress.o: uncompress.cpp HCTree.hpp Helper.hpp
	$(CXX) $(CXXFLAGS) -c uncompress.cpp

HCTree.o: HCTree.cpp HCTree.hpp
	$(CXX) $(CXXFLAGS) -c HCTree.cpp

Helper.o: Helper.cpp Helper.hpp
	$(CXX) $(CXXFLAGS) -c Helper.cpp

clean:
	rm -f *.o compress uncompress
