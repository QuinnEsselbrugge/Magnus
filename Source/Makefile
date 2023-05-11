PRODUCT=Magnus

CFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -Iproduct -Iproduct/interfaces -std=c++17

SOURCES=$(wildcard src/*.cpp) $(wildcard inc/*.cpp)
HEADERS=$(wildcard inc/*.h) \

LIBS=-lpthread

CC=g++

.phony: all clean klocwork klocwork_after_makefile_change

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CC) $(CFLAGS) $(SOURCES)  -lncurses -lpanel -lmenu -o $@ $(LIBS)

clean:
	@rm -rf $(PRODUCT) $(TEST)
	@rm -rf kwinject.out .kwlp .kwps


klocwork:
	@kwcheck run

klocwork_after_makefile_change: clean
	@/opt/klocwork/kwenv.sh
	@kwcheck run
