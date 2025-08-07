CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror
CXX      = g++

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

main: main.o Point.o Heap.o WordList.o
	${CXX} $(CXXFLAGS) -o $@ $+

main.o: main.cpp WordList.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

WordList.o: WordList.cpp WordList.h Heap.h Point.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Heap.o: Heap.cpp Heap.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Point.o: Point.cpp Point.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

test.o: test.cpp Heap.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

test: test.o Heap.o
	${CXX} $(CXXFLAGS) -o $@ $+

clean:
	rm -f main main.o Point.o Heap.o WordList.o test test.o
