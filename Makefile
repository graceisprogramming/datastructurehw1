CC = gcc
CFALGS = -Wall -g -lm

TARGET = sparse_matrix

SRCS = main.c input_store.c operations.c sparse_matrix.c utility.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFALGS) -o $@ $^

main.o: input_store.h operations.h sparse_matrix.h utility.h
input_store.o: input_store.h sparse_matrix.h
operations.o: operations.h sparse_matrix.h input_store.h utility.h
utility.o: utility.h sparse_matrix.h operations.h

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: clean