CC = tcc
CFLAGS = -c -D__OPTIMIZE__ -Wall -Werror -Wunsupported -Wwrite-strings -Wimplicit-function-declaration
LDFLAGS = -vv -shared -lOPENGL32 -lGLU32 -Wl,-subsystem=windows

SOURCE_FILES = main.c opengl.c draw.c

BUILD_DIR = build/
SRC_DIR = src/
OBJ_DIR = $(BUILD_DIR)obj/
TARGET = $(BUILD_DIR)app.exe
SOURCES = $(SOURCE_FILES:%=$(SRC_DIR)%.o)
OBJECTS = $(SOURCE_FILES:%.c=$(OBJ_DIR)%.o)

.PHONY: all clean

all: $(TARGET)
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o$@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJ_DIR)
	$(CC) $< $(CFLAGS) -o$@

$(OBJ_DIR): $(BUILD_DIR)
	mkdir $(OBJ_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR )
