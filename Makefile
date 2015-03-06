CC          := g++

CFLAGS      := -std=c++11 -Wall -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

BASE        := HB/Base
SFML        := HB/SFML

MODULES     := $(BASE) $(SFML)

SOURCES     := $(shell find ./ -maxdepth 1 -name '*.cpp')
INCLUDES    := $(shell find ./ -maxdepth 1 -name '*.h')
STATIC_LIBS = $(shell find ./ -name '*.a')

OBJ         := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

EXE         := exe

.PHONY: $(BASE) $(SFML) $(BOX2D) clean run

all: $(MODULES) $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(STATIC_LIBS) $(CFLAGS)

%.o: %.cpp $(STATIC_LIBS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BASE):
	@$(MAKE) -C $@;

$(SFML): $(BASE)
	@$(MAKE) -C $@;

clean-$(BASE):
	@$(MAKE) -C $(BASE) clean;

clean-$(SFML):
	@$(MAKE) -C $(SFML) clean;
	
clean: clean-$(BASE) clean-$(SFML)
	rm -rf exe *~ *.o *.a

run: all
	./$(EXE)
