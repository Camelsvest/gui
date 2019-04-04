C++ := g++
AR  := ar

MINIGUI_INCLUDE=-I/usr/local/include/minigui
MINIGUI_LIB=-L/usr/local/lib -lminigui_procs

DEFINES := 
INCLUDE := -Iinclude $(MINIGUI_INCLUDE) 

CPPFLAGS  := -g -O0 -Wall -pthread $(DEFINES) $(INCLUDE)

LDFLAGS := -pthread
LIBS    := $(MINIGUI_LIB) -lpng -ljpeg

SOURCE  := $(wildcard src/*.cpp)
OBJS    := $(patsubst %.cpp, %.o, $(SOURCE))

TARGET := gui

.PHONY : all objs clean rebuild

all : $(TARGET)

objs : $(OBJS)

%o : %cpp
	$(C++) $(CPPFLAGS) -c $<

rebuild : clean all

clean:
	@rm -rf src/*.o
	@rm -rf $(TARGET)

$(TARGET) : $(OBJS)
	$(C++) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)
