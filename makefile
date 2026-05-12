CC = g++
SRC = src
BUILD = build/application
CFLAGS = $(SRC)/{main,base-files/std-mem-man,editor/editor,base-files/lines-counter}.cpp -o $(BUILD)/start.bin

make: 
	$(CC) $(CFLAGS)

make_all:
	$(CC) $(CFLAGS)

install:
	$(CC) $(CFLAGS)
	sudo cp $(BUILD)/start.bin /usr/local/bin/jelly

