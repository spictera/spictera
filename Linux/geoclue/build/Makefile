# Define the programs and objects
AGENT = agent
AGENTOBJS = interface/geoclue-agent-interface.o \
	../demo/gclue-service-agent.o \
	../demo/agent.o

# Define the compilation and linking flags
LFLAGS = -l notify -l glib-2.0 -l gio-2.0 -l gobject-2.0 -lm -l gdk_pixbuf-2.0 
CFLAGS = -I/usr/include/glib-2.0 \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-pthread -I/usr/include/gio-unix-2.0 \
	-I/usr/include/libmount \
	-I/usr/include/blkid \
	-I/usr/include/glib-2.0 \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-I/usr/include/gdk-pixbuf-2.0 \
	-I/usr/include/libpng16 \
	-I/usr/include/x86_64-linux-gnu \
	-I/usr/include/libgeoclue-2.0 \
	-Iinterface \
	-I .

# Rule to build getlocation
$(AGENT): $(AGENTOBJS)
	$(CC) -o $@ $(AGENTOBJS) $(LFLAGS)

# Rule to build all
all: $(AGENT)

# Generic rule for compiling C files to object files
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove compiled files
clean:
	rm -f $(AGENT) $(AGENTOBJS)
