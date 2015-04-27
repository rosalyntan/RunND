RM = rm -f

CPPFLAGS = -g  -Werror -Wno-parentheses

CPP_FILES = RunND.cpp LTexture.cpp Object.cpp Background.cpp

DEPENDS = $(CPP_FILES:.cpp=.d)
OBJECTS = $(CPP_FILES:.cpp=.o)

LIBS = -lSDL2 -lSDL2_image

all: main

main: $(OBJECTS)
	g++ $(CPPFLAGS) -o $@ $^ $(LIBS)

%.d: %.cpp
	g++ -MM -MF $@ $<

%.o: %.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

-include $(DEPENDS)

.PHONY: clean

clean:
	$(RM) main
	$(RM) $(DEPENDS)
	$(RM) $(OBJECTS)

