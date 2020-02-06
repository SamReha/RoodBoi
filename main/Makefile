SOURCE = \
	FixedWidthTypes.h \
	main.cpp

make:
	for s in $(SOURCE); do \
		$(CXX) $$s -o main.o $(SFML_LIBS) $(LIBS); \
	done

clean:
	rm main.o
