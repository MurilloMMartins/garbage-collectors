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

$(TARGET): $(SRC_DIR)main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^
	
test: $(TEST_DIR)main_test.c $(TEST_DIR)munit/munit.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)main_test $^
	
clean:
ifeq ($(strip $(BUILD_DIR)),)
	rm -f $(BINARY)
else
	rm -r $(BUILD_DIR)
endif

all: $(TARGET)
	
run: $(TARGET)
	./$<
	
run-test: test
	./$(BUILD_DIR)main_test