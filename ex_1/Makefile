SRC_DIR = ./src
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
TARGET_DIR = ./build
TARGET = $(TARGET_DIR)/ex_1
BUILD_COMMAND = gcc $(SOURCES) -o $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p $(TARGET_DIR)
	$(BUILD_COMMAND)

run: $(TARGET)
	$(TARGET)

debug: $(TARGET)
	gdb --args ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean
