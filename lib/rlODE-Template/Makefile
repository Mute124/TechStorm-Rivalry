
APPNAME:=$(shell basename `pwd`)

INSTR:= -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract
INSTR+= -fno-omit-frame-pointer

LDFLAGS:=-L ../raylib/src -lm -lraylib -lX11 -ldl -pthread -L lib
LDFLAGS+=-L ode/ode/src/.libs/ -lode -lstdc++

CFLAGS:= -Wfatal-errors -pedantic -Wall -Wextra -Werror -I ode/include/
CFLAGS+= -std=c99 -I ./include -I ../raylib/src -DPLATFORM_DESKTOP

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=.build/%.o)
INC:=$(wildcard include/*.h)

CC=gcc

all: debug

$(APPNAME): $(OBJ)
	$(CC) $(OBJ) -o $(APPNAME) $(LDFLAGS)

$(OBJ): .build/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: debug release inst

debug: CFLAGS+= -g
debug: 
	@echo "*** made DEBUG target ***"

release: CFLAGS+= -O3
release: 
	@echo "*** made RELEASE target ***"

inst: CFLAGS+= -g $(INSTR)
inst: LDFLAGS+= $(INSTR)
inst: 
	@echo "*** made INSTRUMENTATION target ***"

release: CFLAGS+= -Ofast

debug release inst: clean $(APPNAME)

.PHONY:	clean
clean:
	rm .build/* -f
	rm $(APPNAME) -f

style: $(SRC) $(INC)
	astyle -A10 -s4 -S -p -xg -j -z2 -n src/* include/*
