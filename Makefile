CSTD:=99
CFLAGS:=-Wall -Werror 
ASAN:=n

TEST_DIR:=tests/
BUILD_DIR:=build/
SRC_DIR:=src/
INCLUDE_DIR:=include/
BINARY:=main

TARGET:=$(BUILD_DIR)$(BINARY)

ifeq ($(ASAN),y)
	CFLAGS+=-fsanitize=address
endif

$(BUILD_DIR):
	mkdir $@

$(TARGET): $(SRC_DIR)main.c $(SRC_DIR)langobject.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	
object_test: $(TEST_DIR)object_test.c $(TEST_DIR)munit/munit.c $(SRC_DIR)langobject.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)$@ $^
	
clean:
ifeq ($(strip $(BUILD_DIR)),)
	rm -f $(BINARY)
else
	rm -r $(BUILD_DIR)
endif

all: $(TARGET)
	
run: $(TARGET)
	./$<
	
run-test: object_test
	./$(BUILD_DIR)object_test