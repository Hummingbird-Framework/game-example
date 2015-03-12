CC        := g++

CFLAGS    := -std=c++11 -Wall -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

STATIC_LIB_NAME := Hummingbird-SFML-2.1

SOURCES   := $(shell find ./ -name '*.cpp')
INCLUDES  := $(shell find ./ -name '*.h')

OBJ       := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

all: $(OBJ)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) -O3
	ar rvs $(STATIC_LIB_NAME).a $@

.PHONY: clean

clean:
	rm -rf *~ *.o *.a
