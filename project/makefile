CMP = g++
MAIN = animate
FUNC = Object
FLAGS = -lSDL2 -lSDL2_image

all: $(MAIN)

$(MAIN): $(MAIN).o $(FUNC).o
	$(CMP) $(MAIN).o $(FUNC).o -o $(MAIN) $(FLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CMP) -c $(MAIN).cpp $(FLAGS)

$(FUNC).o: $(FUNC).cpp
	$(CMP) -c $(FUNC).cpp $(FLAGS)

clean:
	rm *.o $(MAIN) *~
