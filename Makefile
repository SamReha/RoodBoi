LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++
SFML_INCLUDE=-I/Users/samreha/SFML-2.4.2-osx-clang/include
SFML_LIBS=-L/Users/samreha/SFML-2.4.2-osx-clang/lib

MOD_DIRS = \
	cpu \
	graphics \
	main \
	memory \
	sound

all: roodboi
	@echo "Build Successful!"

roodboi:
	for path in $(MOD_DIRS); do \
		 $(MAKE) -C $$path; \
	done

	$(CXX) -o roodboi.exe $(wildcard build/*.o) $(SFML_LIBS) $(LIBS)

clean:
	rm build/*.o
	rm roodboi.exe
