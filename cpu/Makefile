SOURCE = \
	CentralProcessingUnit.h \
	CentralProcessingUnit.cpp

make:
	for s in $(SOURCE); do \
		$(CXX) $$s -o CentralProcessingUnit.o $(SFML_LIBS) $(LIBS); \
	done

clean:
	rm CentralProcessingUnit.o
