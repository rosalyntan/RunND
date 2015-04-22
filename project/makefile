CMP = g++
MAIN = RunND
FUNC = LTexture
FUNC1 = Object
FUNC2 = Background
FUNC3 = Runner
FLAGS = -lSDL2 -lSDL2_image

all: $(MAIN)

$(MAIN): $(MAIN).o $(FUNC).o $(FUNC1).o $(FUNC2).o $(FUNC3).o
	$(CMP) $(MAIN).o $(FUNC).o $(FUNC1).o $(FUNC2).o $(FUNC3).o -o $(MAIN) $(FLAGS)

$(MAIN).o: $(MAIN).cpp
	$(CMP) -c $(MAIN).cpp $(FLAGS)

$(FUNC).o: $(FUNC).cpp
	$(CMP) -c $(FUNC).cpp $(FLAGS)

$(FUNC1).o: $(FUNC1).cpp
	$(CMP) -c $(FUNC1).cpp $(FLAGS)

$(FUNC2).o: $(FUNC2).cpp
	$(CMP) -c $(FUNC2).cpp $(FLAGS)

$(FUNC3).o: $(FUNC3).cpp
	$(CMP) -c $(FUNC3).cpp $(FLAGS)

clean:
	rm *.o $(MAIN) *~
