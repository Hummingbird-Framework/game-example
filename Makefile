CC          := g++

CFLAGS      := -std=c++11 -Wall -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -ltinyxml2 -lz -ltmxparser

BASE        := HB/Core
SFML        := HB/SFML
TMX        := HB/Tmx

MODULES     := $(BASE) $(SFML) $(TMX)

SOURCES     := $(shell find ./ -maxdepth 1 -name '*.cpp')
INCLUDES    := $(shell find ./ -maxdepth 1 -name '*.h')
STATIC_LIBS = $(shell find ./ -name '*.a')

OBJ         := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

EXE         := exe

.PHONY: $(BASE) $(SFML) $(TMX) clean run

all: $(MODULES) $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(STATIC_LIBS) $(CFLAGS)

%.o: %.cpp $(STATIC_LIBS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BASE):
	@$(MAKE) -C $@;

$(SFML): $(BASE)
	@$(MAKE) -C $@;

$(TMX): $(SFML)
	@$(MAKE) -C $@;

clean-$(BASE):
	@$(MAKE) -C $(BASE) clean;

clean-$(SFML):
	@$(MAKE) -C $(SFML) clean;

clean-$(TMX):
	@$(MAKE) -C $(TMX) clean;
	
clean:
	rm -rf exe *~ *.o *.a

clean-all: clean-$(BASE) clean-$(SFML) clean-$(TMX) clean

run: all
	./$(EXE)
