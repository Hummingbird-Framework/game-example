CC          := g++

CFLAGS      := -std=c++11 -Wall -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lBox2D -ltinyxml2 -lz -ltmxparser

BASE        := HB/Core
SFML        := HB/SFML
TMX         := HB/Tmx
BOX2D       := HB/Box2D

MODULES     := $(BASE) $(SFML) $(TMX) $(BOX2D)

SOURCES     := $(shell find ./ -maxdepth 1 -name '*.cpp')
INCLUDES    := $(shell find ./ -maxdepth 1 -name '*.h')
STATIC_LIBS = ./HB/SFML/Hummingbird-SFML-2.1.a ./HB/Box2D/Hummingbird-Box2D.a ./HB/Tmx/Hummingbird-Tmx.a ./HB/Core/Hummingbird-Base.a

OBJ         := $(addprefix ./,$(SOURCES:./%.cpp=%.o))

EXE         := exe

.PHONY: $(BASE) $(SFML) $(TMX) $(BOX2D) clean run

all: $(MODULES) $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ) $(STATIC_LIBS) $(CFLAGS) -O3

%.o: %.cpp $(STATIC_LIBS)
	$(CC) -c -o $@ $< $(CFLAGS) -O3

$(BASE):
	@$(MAKE) -C $@;

$(SFML): $(BASE)
	@$(MAKE) -C $@;

$(TMX): $(SFML)
	@$(MAKE) -C $@;

$(BOX2D): $(BASE)
	@$(MAKE) -C $@;

clean-$(BASE):
	@$(MAKE) -C $(BASE) clean;

clean-$(SFML):
	@$(MAKE) -C $(SFML) clean;

clean-$(TMX):
	@$(MAKE) -C $(TMX) clean;

clean-$(BOX2D):
	@$(MAKE) -C $(BOX2D) clean;
	
clean:
	rm -rf exe *~ *.o *.a

clean-all: clean-$(BASE) clean-$(BOX2D) clean-$(SFML) clean-$(TMX) clean

run: all
	./$(EXE)
