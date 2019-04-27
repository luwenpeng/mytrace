.PHONY: all install clean

CXX = gcc

#CFLAGS = -Wall -g -fsanitize=leak -fsanitize=address
#LIB = -lasan

CFLAGS = -O2
LIB = 

INCLUDES = 
BIN = mytrace
INSTALLDIR = /usr/sbin/

OBJS = mytrace.o

all: $(BIN)
$(BIN): $(OBJS)
	$(CXX) $^ -o $@ $(LIB)

%.o: %.c
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

install:
	test -d $(INSTALLDIR) || mkdir $(INSTALLDIR)
	cp $(BIN) $(INSTALLDIR)

clean:
	rm -rf $(BIN) $(OBJS)
