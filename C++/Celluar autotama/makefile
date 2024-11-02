MAIN           = Test
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1            = Cells
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT1_SOURCE    = $(ADT1).cpp
ADT2           = Grid
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
ADT2_SOURCE    = $(ADT2).cpp


$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) 
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	rm *.o
	rm Test