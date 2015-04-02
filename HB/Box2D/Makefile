CC        := g++

CFLAGS    := -std=c++11 -Wall -lBox2D

STATIC_LIB_NAME := Hummingbird-Box2D

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
