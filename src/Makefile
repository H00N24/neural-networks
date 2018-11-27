CC=gcc
CFLAGS=-lm
OPTIMIZATION=-O2
HEADERS=*.h 
C_FILES=*.c
DEBUG=-D DEBUG
TARGET=network

TEST_TARGET=test
TEST_C_FILES=tests/*.c
TEST_H_FILES=tests/*.h

default: $(TARGET)

$(TARGET): $(C_FILES) $(HEADERS)
	$(CC) -o $(TARGET) $(C_FILES) $(HEADERS) $(CFLAGS) $(OPTIMIZATION)

debug:
	$(CC) -o $(TARGET) $(C_FILES) $(HEADERS) $(CFLAGS) $(OPTIMIZATION) $(DEBUG)

test:
	$(CC) -o $(TEST_TARGET) $(TEST_C_FILES) matrix.c $(TEST_H_FILES) matrix.h $(CFLAGS)

clean:
	rm $(TARGET) $(TEST_TARGET)
