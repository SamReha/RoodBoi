SOURCE = \
	SoundProcessor.h \
	SoundProcessor.cpp

make:
	for s in $(SOURCE); do \
		$(CXX) $$s -o SoundProcessor.o $(SFML_LIBS) $(LIBS); \
	done

clean:
	rm SoundProcessor.o
