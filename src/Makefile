CC=gcc
CFLAGS=-lm
OPTIMALIZATION=-O2
HEADERS=*.h 
C_FILES=*.c
DEBUG=-D DEBUG
TAERGET=network

default: $(TAERGET)

$(TAERGET): $(C_FILES) $(HEADERS)
	$(CC) -o $(TAERGET) $(C_FILES) $(HEADERS) $(CFLAGS) $(OPTIMALIZATION)

debug:
	$(CC) -o $(TAERGET) $(C_FILES) $(HEADERS) $(CFLAGS) $(OPTIMALIZATION) $(DEBUG)


clean:
	rm $(TAERGET)