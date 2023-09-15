
LDFLAGS:=-L ../raylib/src -lm -lraylib -lX11 -ldl -pthread

CFLAGS:= -g -Wfatal-errors -pedantic -Wall -Wextra -Werror
CFLAGS+= -std=c99 -I ./include -I ../raylib/src -DPLATFORM_DESKTOP

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)
MAINOBJ:=$(filter-out obj/minimal.o, $(SRC:src/%.c=obj/%.o))
MINOBJ:=$(filter-out obj/models_simple_lighting.o, $(SRC:src/%.c=obj/%.o))
INC:=$(wildcard include/*.h)

CC=gcc

all: models_simple_lighting minimal

minimal: $(MINOBJ)
	$(CC) $(MINOBJ) -o minimal $(LDFLAGS)

models_simple_lighting: $(MAINOBJ)
	$(CC) $(MAINOBJ) -o models_simple_lighting $(LDFLAGS)

$(OBJ): obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: debug release
debug: CFLAGS+= -g
release: CFLAGS+= -O3

debug release: clean models_simple_lighting minimal

.PHONY:	clean
clean:
	rm obj/* -f
	rm models_simple_lighting -f
	rm minimal -f

style: $(SRC) $(INC)
	astyle -A10 -s4 -S -p -xg -j -z2 -n src/* include/*
