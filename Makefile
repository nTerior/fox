CC = gcc
CFLAGS =
LDFLAGS = -lncurses -lpthread
SRC_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
INCLUDE_DIR = -Iinclude/

.PHONY: clean install uninstall

debug: CFLAGS += -g
release: CFLAGS += -O3

debug: fox
release: fox

fox: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $@ -Wall -Wextra

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $< -c -o $@ -Wall -Wextra

clean:
	rm -f fox
	rm -f $(OBJ_FILES)

install:
	install --mode=755 fox /usr/bin/

uninstall:
	rm -f /usr/bin/fox
