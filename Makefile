CFLAGS = -std=c99

nwork : nwork.o sockstuff.o

nwork.o : sockstuff.h
sockstuff.o : sockstuff.h
