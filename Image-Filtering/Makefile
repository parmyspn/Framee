EXENAME = framee
OBJS = main.o PNG.o HSLAPixel.o lodepng.o framee.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp framee.h  cs221util/PNG.h cs221util/HSLAPixel.h 
	$(CXX) $(CXXFLAGS) main.cpp 

framee.o : framee.cpp framee.h
	$(CXX) $(CXXFLAGS) framee.cpp
	
PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp


test: basic.o PNG.o HSLAPixel.o lodepng.o framee.o 
	$(LD) basic.o PNG.o HSLAPixel.o lodepng.o framee.o  $(LDFLAGS) -o test

basic.o : tests/basic.cpp tests/catch.hpp
	$(CXX) $(CXXFLAGS) tests/basic.cpp


clean :
	-rm -f *.o $(EXENAME) test
