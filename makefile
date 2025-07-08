# general flags
CC = gcc
CFLAGS = -std=c11 -g -I$(SRC_DIR) -Wall -Wformat=2 -Wextra -Wconversion -Wno-sign-conversion -Wdouble-promotion -Wno-unused-parameter -Wno-unused-function -Wcast-qual -Walloc-zero -Wduplicated-branches -Wduplicated-cond -Wfloat-equal

# directories
SRC_DIR = src
BUILD_DIR = build

# rule for making bulid dir
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 01
#
# rule for building build/01
$(BUILD_DIR)/01: $(BUILD_DIR)/01.o $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/01.o: $(SRC_DIR)/01.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 02
#
# rule for building build/01
$(BUILD_DIR)/02: $(BUILD_DIR)/02.o $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/02.o: $(SRC_DIR)/02.c $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*

.PHONY: clean
