# DIR 
BIN = ../../bin
REDIS = ../Con2redis/

# Targets
TARGETS = $(BIN)/client
ODIR = obj
SDIR = src
IDIR = inc

# Variables
CC=g++
CFLAGS=-std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -I$(REDIS)$(IDIR) -I$(IDIR) -lpq -lm -lhiredis

# Client
DEPS = $(wildcard $(REDIS)$(IDIR)/*.h)
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

# Redis
REDIS_OBJ = $(wildcard $(REDIS)$(ODIR)/*.o)

all: $(TARGETS)

# Compiling all
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN)/client: $(OBJ) $(DEPS)
	$(CC) -o $@ $(OBJ) $(REDIS_OBJ) $(CFLAGS)
