CC        := g++

CFLAGS    := -std=c++11 -Wall

STATIC_LIB_NAME := Hummingbird-Base

SOURCES   := $(shell find ./ -name '*.cpp')
INCLUDES  := $(shell find ./ -name '*.h')

OBJ       := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

all: $(OBJ)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	ar rvs $(STATIC_LIB_NAME).a $@

.PHONY: clean

clean:
	rm -rf *~ *.o *.a
