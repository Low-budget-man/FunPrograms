MAIN           = entitytest
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1           = entity
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT1_SOURCE    = $(ADT1).cpp

$(MAIN): $(OBJECT) $(ADT1_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT)

$(OBJECT): $(SOURCE) 
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)
clean:
	rm *.o
	rm $(MAIN)
