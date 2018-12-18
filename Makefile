#TODO: remove the Character binding here

CC=g++
LD=g++

HEADERS = -Ilib/SDL2/include/SDL2 \
-Ilib/SDL_ttf/include/SDL2 \
-Ilib/SDL_image/include/SDL2 \
-Iengine/base/include

LDFLAGS = -Llib/SDL2/lib \
-Llib/SDL_ttf/lib \
-Llib/SDL_image/lib \
-lSDL2main \
-lSDL2 \
-lSDL2_ttf \
-lSDL2_image \
-lfreetype \
-lpthread \
-ldl \
-lrt

CFLAGS = -std=c++0x

SOURCES = \
engine/base/src/main.cpp \
engine/base/src/MainEngine.cpp \
engine/base/src/Utils.cpp \
engine/base/src/Subtask.cpp \
engine/base/src/Yobject.cpp \
engine/base/src/Timer.cpp \
engine/base/src/PluginList.cpp \
engine/base/src/Task.cpp \
engine/base/src/TaskManager.cpp \
engine/base/src/TaskManagerInterface.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = bin/yaak


all: release

release: CFLAGS += -O3
release: executable

debug: CFLAGS += -g -DDEBUG_OUTPUT
debug: executable

executable: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o  $(TARGET)

%.o: %.cpp
	$(CC) $(CFLAGS) $(HEADERS)  -c $< -o $@
	
clean:
	rm -f engine/base/src/*.o
