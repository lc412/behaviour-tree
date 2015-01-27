# Compiler and Linker settings
CC = clang++
COMPILER_FLAGS = -std=c++11 -llua -ldl
LIBRARIES = 
LINKER_FLAGS =

# Directories
EXE_DIR = executables
INPUT_DIR = input
OUTPUT_DIR = output
SOURCE_DIR = src
INCLUDE_DIR = $(SOURCE_DIR)/include
BACKUP_DIR = backup

# Files
DRIVER_FILE = $(SOURCE_DIR)/Driver.cpp
INCLUDE_FILES = $(shell find $(INCLUDE_DIR) -name *.cpp)
HEADER_FILES = $(shell find $(INCLUDE_DIR) -name *.h)
FILES = $(DRIVER_FILE) $(INCLUDE_FILES)
OUT = $(EXE_DIR)/Driver

# Targets
.PHONY: uninstall output_clean backup

install: output_clean
	mkdir $(EXE_DIR)
	-mkdir $(INPUT_DIR)
	mkdir $(OUTPUT_DIR)

build: install
	$(CC) $(FILES) -o $(OUT) $(COMPILER_FLAGS) $(LIBRARIES) $(LINKER_FLAGS)

rebuild: output_clean build

output_clean:
	rm -fr $(EXE_DIR)
	rm -fr $(OUTPUT_DIR)

uninstall:
	rm -fr $(INPUT_DIR)/*
	rm -fr $(EXE_DIR)
	rm -fr $(INPUT_DIR)
	rm -fr $(OUTPUT_DIR)

backup:
	mkdir $(BACKUP_DIR)
	cp -r $(EXE_DIR) $(BACKUP_DIR)/$(EXE_DIR)
	cp -r $(INPUT_DIR) $(BACKUP_DIR)/$(INPUT_DIR)
	cp -r $(OUTPUT_DIR) $(BACKUP_DIR)/$(OUTPUT_DIR)
	cp -r $(SOURCE_DIR) $(BACKUP_DIR)/$(SOURCE_DIR)
