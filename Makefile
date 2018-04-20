LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
SFML_INCLUDE=-I/Users/samreha/SFML-2.4.2-osx-clang/include
SFML_LIBS=-L/Users/samreha/SFML-2.4.2-osx-clang/lib

all: roodboi
	@echo "Build successful!"

%.o: src/%.cpp
	$(CXX) -Wall -g -std=c++11 -c $< $(SFML_INCLUDE) -o $@

%.o: src/%.h
	$(CXX) -Wall -g -std=c++11 -c $< $(SFML_INCLUDE) -o $@

roodboi: CentralProcessingUnit.o MemoryManager.o PictureProcessor.o SoundProcessor.o main.o
	$(CXX) -o build/roodboi CentralProcessingUnit.o MemoryManager.o PictureProcessor.o SoundProcessor.o main.o $(SFML_LIBS) $(LIBS)

clean:
	rm -f build/roodboi *.o
