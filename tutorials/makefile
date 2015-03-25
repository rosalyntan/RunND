CMP = g++
MAIN1 = CApp
MAIN2 = Capp_OnInit
MAIN3 = Capp_OnEvent
MAIN4 = Capp_OnLoop
MAIN5 = Capp_OnRender
MAIN6 = Capp_OnCleanup
EXEC1 = $(MAIN1)
EXEC2 = $(MAIN2)
EXEC3 = $(MAIN3)
EXEC4 = $(MAIN4)
EXEC5 = $(MAIN5)
EXEC6 = $(MAIN6)
FLAGS = -lSDL2

all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) 

$(EXEC1): $(MAIN1).cpp
	$(CMP) $(MAIN1).cpp -o $(EXEC1) $(FLAGS) 

$(EXEC2): $(MAIN2).cpp
	$(CMP) $(MAIN2).cpp -o $(EXEC2) $(FLAGS) 

$(EXEC3): $(MAIN3).cpp
	$(CMP) $(MAIN3).cpp -o $(EXEC3) $(FLAGS) 

$(EXEC4): $(MAIN4).cpp
	$(CMP) $(MAIN4).cpp -o $(EXEC4) $(FLAGS) 

$(EXEC5): $(MAIN5).cpp
	$(CMP) $(MAIN5).cpp -o $(EXEC5) $(FLAGS) 

$(EXEC6): $(MAIN6).cpp
	$(CMP) $(MAIN6).cpp -o $(EXEC6) $(FLAGS) 

clean:
	rm $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5) $(EXEC6) 
