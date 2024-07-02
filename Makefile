# Define the programs and objects
GETLOCATION = getlocation
GETLOCATIONOBJS = getlocation.o

# Define the compilation and linking flags
CFLAGS = $(shell pkg-config --cflags libgeoclue-2.0 dbus-1) -pthread
LFLAGS = $(shell pkg-config --libs libgeoclue-2.0 dbus-1) -pthread

# Rule to build getlocation
$(GETLOCATION): $(GETLOCATIONOBJS)
	$(CC) -o $@ $(GETLOCATIONOBJS) $(LFLAGS)

# Rule to build all
all: $(GETLOCATION)

# Generic rule for compiling C files to object files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(GETLOCATION) $(GETLOCATIONOBJS)