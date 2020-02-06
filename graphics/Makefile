SOURCE = \
	PictureProcessor.h \
	PictureProcessor.cpp

make:
	for s in $(SOURCE); do \
		$(CXX) $$s -o PictureProcessor.o $(SFML_LIBS) $(LIBS); \
	done

clean:
	rm PictureProcessor.o
