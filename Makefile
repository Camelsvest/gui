C++ := g++
AR  := ar

MINIGUI_INCLUDE=-I/usr/local/include/minigui
MINIGUI_LIB=-L/usr/local/lib -lminigui_ths -lmgncs

LOGGING_INCLUDE=-Ilogging
LOGGING_LIB= #-Llogging -llogging

DEFINES := 
INCLUDE := -Iinclude $(MINIGUI_INCLUDE) $(LOGGING_INCLUDE)

CPPFLAGS  := -g -O0 -Wall -pthread $(DEFINES) $(INCLUDE)

LDFLAGS := -pthread
#-lts
LIBS    := $(LOGGING_LIB) $(MINIGUI_LIB) -lts -lpng -ljpeg -lm -ldl -lfreetype

SOURCE  := $(wildcard src/*.cpp)
OBJS    := $(patsubst %.cpp, %.o, $(SOURCE))

LOGGING = #liblogging.a
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
	#make -C ./logging clean

$(TARGET) : $(OBJS) $(LOGGING)
	$(C++) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(LOGGING):
	make -C ./logging
