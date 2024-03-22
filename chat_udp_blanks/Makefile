FML_PATH=/usr/local/SFML-2.2/
# SFML_PATH=/usr/local/Cellar/sfml/2.5.1/
CXXFLAGS= -std=c++14 -Wall -Wpedantic -I${SFML_PATH}include/
LDFLAGS=-L${SFML_PATH}lib/
CFLAGS=-g -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread
CPPFLAGS=
LDLIBS=
LIBS=
CPP=g++

all: client server

server: server.o receiver.o
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(SFML_PATH)/lib/:lib $(CPP) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $^ -o $@ $(CFLAGS)

client: client.o receiver.o
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(SFML_PATH)/lib/:lib $(CPP) $(CXXFLAGS) $(LDFLAGS) $(LIBS) $^ -o $@ $(CFLAGS)

runc: client
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(SFML_PATH)/lib/:lib ./client

runs: server
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):$(SFML_PATH)/lib/:lib ./server

clean:
	\rm -f *.o client server
