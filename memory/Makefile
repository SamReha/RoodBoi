SOURCE = \
	MemoryManager.h \
	MemoryManager.cpp

make:
	for s in $(SOURCE); do \
		$(CXX) $$s -o MemoryManager.o $(SFML_LIBS) $(LIBS); \
	done

clean:
	rm MemoryManager.o
