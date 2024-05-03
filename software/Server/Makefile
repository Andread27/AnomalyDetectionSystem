# DIR 
BIN = ../../bin
REDIS = ../Con2redis
PSQL = ../Con2db

# Targets
TARGETS = con2redis $(BIN)/server
ODIR = obj
SDIR = src
IDIR = inc

# Variables
CC=g++
CFLAGS=-std=c++20 -g -ggdb -fpermissive -L/usr/local/lib -Wall -I. -I$(REDIS)$(IDIR) -I$(IDIR) -I/usr/include/postgresql -lpq -lm -lhiredis

# Server
DEPS = $(wildcard $(REDIS)/$(IDIR)*.h)
SRC = $(wildcard $(SDIR)/*.cpp)
OBJ = $(patsubst $(SDIR)/%.cpp, $(ODIR)/%.o, $(SRC))

# Redis and PostgreSQL
REDIS_OBJ = $(wildcard $(REDIS)/$(ODIR)/*.o)
PSQL_OBJ = $(wildcard $(PSQL)/$(ODIR)/*.o)

# Compiling all
all: $(TARGETS)

con2redis:
	$(MAKE) -C $(REDIS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN)/server: $(OBJ) $(DEPS)
	$(CC) -o $@ $(OBJ) $(REDIS_OBJ) $(PSQL_OBJ) $(CFLAGS)
