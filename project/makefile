CMP = g++
MAIN = animate
EXEC = $(MAIN)
FLAGS = -lSDL2 -lSDL2_image
TARGETS = $(EXEC)

all: $(TARGETS)

$(EXEC): $(MAIN).cpp
	$(CMP) $(FLAGS) $(MAIN).cpp -o $(EXEC)

clean:
	rm $(TARGETS)
