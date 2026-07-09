CC = gcc
CFLAGS = -Wall -g -I./include
SRC = src/graph_adjlist.c src/main.c
OBJ = graph_adjlist.o main.o
TARGET = graph_adjlist_demo

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf *.o $(TARGET)