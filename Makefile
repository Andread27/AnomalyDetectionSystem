# Targets
TARGETS = create_bin con2redis con2db client server 
SDIR = src
IDIR = inc
ODIR = obj

# DIR Client, Server, Redis and Postgres
CLIENT = project/Client
SERVER = project/Server
REDIS = project/Con2redis
PSQL = project/Con2db


# Compiling all
all: $(TARGETS)

# Create bin folder
create_bin:
	mkdir -p bin
	
# Redis
con2redis:
	$(MAKE) -C $(REDIS)

# PostgreSQL
con2db:
	$(MAKE) -C $(PSQL)

# CLIENT
client:
	$(MAKE) -C $(CLIENT)
	
server:
	$(MAKE) -C $(SERVER)

.PHONY: clean

clean:
	rm -f $(CLIENT)/$(ODIR)/*.o 
	rm -f $(SERVER)/$(ODIR)/*.o
	rm -f $(REDIS)/$(ODIR)/*.o
	rm -f $(PSQL)/$(ODIR)/*.o
	rm -rf bin


