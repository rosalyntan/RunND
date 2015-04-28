CMP = g++
MAIN = RunND
FUNC = LTexture
FUNC1 = Object
FUNC2 = Coin
FUNC3 = Obstacle
FUNC4 = Background
FUNC5 = Runner
FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(MAIN)

$(MAIN): $(MAIN).o $(FUNC).o $(FUNC1).o $(FUNC2).o $(FUNC3).o $(FUNC4).o $(FUNC5).o
	$(CMP) $(MAIN).o $(FUNC).o $(FUNC1).o $(FUNC2).o $(FUNC3).o $(FUNC4).o $(FUNC5).o -o $(MAIN) $(FLAGS)

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

$(FUNC4).o: $(FUNC4).cpp
	$(CMP) -c $(FUNC4).cpp $(FLAGS)

$(FUNC5).o: $(FUNC5).cpp
	$(CMP) -c $(FUNC5).cpp $(FLAGS)

clean:
	-rm *.o $(MAIN) *~
