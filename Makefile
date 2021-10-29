# run THOSE TWO (2) (dos) (deux) commands in terminal:
# LD_LIBRARY_PATH=/home/jorinovski/repos/SFML-2.5.0/lib/;export LD_LIBRARY_PATH

# for logging errors (c++ can spill a lot of unreadable template errors)
# make a.mason.out > errors.txt 2>&1

# $(libflags) $(args) $(append_this)
# -ffunction-sections -fdata-sections -Wl,--gc-sections -Wl,--print-gc-sections
# args = -g -std=c++17 -Wunused-function -fsanitize=undefined
args = -g -std=c++17 -Wunused-function -O0 -g3
args = -std=c++17 -Wunused-function -Wall
args = -std=c++17 -Wunused-function
args = -g -std=c++17 -Wunused-function
args = -std=c++17 -Wunused-function -Wall

# LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lubsan
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# LDFLAGS = -lsfml-graphics-s.a -lsfml-window-s.a -lsfml-system-s.a
# LDFLAGS = -lsfml-graphics.dll.a -lsfml-window.dll.a -lsfml-system.dll.a

inclflags = -I/usr/include/ -I/home/jorinovski/repos/SFML-2.5.0/include/
CC = g++ -fdiagnostics-color=always
# CC = clang++

# <IRC> Install valgrind from your package manager or http://valgrind.org/, then compile your program with -O0 -g3, then run valgrind -v --leak-check=full ./myProgram and read the output.

# LD_LIBRARY_PATH=/home/jorinovski/repos/SFML-2.5.0/lib/
# export LD_LIBRARY_PATH
# or this one:
LD_LIBRARY_PATH = -L/home/jorinovski/repos/SFML-2.5.0/lib/
# make -f Makefile-labground


# for MIIINGEWEEEE
# LD_LIBRARY_PATH = -L/c/_code/libs/for-mingw/SFML-2.5.1/lib/
LD_LIBRARY_PATH = -L/c/msys64/mingw64/lib/
inclflags = -I/usr/include/ -I/c/_code/libs/for-mingw/SFML-2.5.1/include -I/c/msys64/mingw32/include/


# $(CC) -c $< -o $@
# $^ == dependencies; $< == first in deps; $@ == target name
# a.text-tests.out: main-text-tests.o 2dhelpers.o Text2.o

# commented because of text2.h
# a.text-tests.out: main-text-tests.o 2dhelpers.o
# 	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)

# a.logistics.out: main-logistics.o 2dhelpers.o poisson_distr.o grid_search.o logistics.o
# a.logistics.out: main-logistics.o 2dhelpers.o poisson_distr.o grid_search.o logistics2.o
a.logistics.out.exe: main-logistics.o 2dhelpers.o poisson_distr.o grid_search.o logistics2.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.recoil.out: main-recoil.o 2dhelpers.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.bars.out: main-bars.o 2dhelpers.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.quadtree.out: main-quadtree.o 2dhelpers.o grid_search.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.mason.out: main-mason.o 2dhelpers.o masonry.o masonry-bottom.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.mason-test.out: main-mason-test.o 2dhelpers.o masonry.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.perlin.out: main-perlin.o 2dhelpers.o masonry.o poisson_distr.o grid_search.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.galax.out: main-galax.o 2dhelpers.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.clocks.out: main-clocks.o 2dhelpers.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.streeter.out: main-streeter.o 2dhelpers.o grid_search.o streetgen.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
a.bags.out: main-bags.o 2dhelpers.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)

# 2d helpers, always needed
2dhelpers.h.gch: 2dhelpers_dont_include.h
	$(CC) -c 2dhelpers_dont_include.h -o 2dhelpers.h.gch $(args) $(inclflags)
2dhelpers.o: 2dhelpers.h.gch 2dhelpers.cc
	$(CC) -c 2dhelpers.cc -o 2dhelpers.o $(args) $(inclflags)

# modules
grid_search.o: grid_search.cpp grid_search.h 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
poisson_distr.o: poisson_distr.cc poisson_distr.h 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
masonry.o: masonry.cpp masonry.h 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)
masonry-bottom.o: masonry-bottom.cpp masonry.h 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)

# commented because of text2.h
# Text2.o: Text2.cpp Text2.h
# 	$(CC) -c Text2.cpp -o Text2.o $(args) $(inclflags)
streetgen.o: streetgen.cc streetgen.h
	$(CC) -c streetgen.cc -o streetgen.o $(args) $(inclflags)
logistics.o: logistics.cpp logistics.h 2dhelpers.h.gch grid_search.h
	$(CC) -c logistics.cpp -o logistics.o $(args) $(inclflags)
logistics2.o: logistics2.cpp logistics2.h 2dhelpers.h.gch grid_search.h
	$(CC) -c $< -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)

# please think about adding headers where there are modules,
# mains

# commented because of text2.h
# main-text-tests.o: main-text-tests.cc 2dhelpers.h.gch
# 	$(CC) -c $< -o $@ $(args) $(inclflags)
# main-logistics.o: main-logistics.cc 2dhelpers.h.gch logistics.h
main-logistics.o: main-logistics.cc 2dhelpers.h.gch logistics2.h
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-recoil.o: main-recoil.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-bars.o: main-bars.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-quadtree.o: main-quadtree.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-mason.o: main-mason.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-mason-test.o: mason-shorter-tests.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-perlin.o: main-perlin.cpp 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-galax.o: main-galax.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-clocks.o: main-clocks.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-streeter.o: main-streeter.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
main-bags.o: main-bags.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)

# more new one
main-2dtests.o: main-2dtests.cc 2dhelpers.h.gch
	$(CC) -c $< -o $@ $(args) $(inclflags)
a.2dtests.out: main-2dtests.o 2dhelpers.o poisson_distr.o grid_search.o
	$(CC) $^ -o $@ $(LDFLAGS) $(args) $(inclflags) $(LD_LIBRARY_PATH)



clean:
	rm *.out *.o *.gch *.out.exe