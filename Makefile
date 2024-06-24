GETLOCATION=getlocation
GETLOCATIONOBJS=getlocation.o
CFLAGS=$(shell pkg-config --cflags libgeoclue-2.0 dbus-1)
LFLAGS=$(shell pkg-config --libs libgeoclue-2.0 dbus-1)

$(GETLOCATION): $(GETLOCATIONOBJS) 
	$(CC) -o $@ $(GETLOCATIONOBJS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(OSVER) $(INC64) -c $< -o $@


