C++ := g++
AR  := ar

MINIGUI_INCLUDE=-I/usr/local/include/minigui
MINIGUI_LIB=-L/usr/local/lib -lminigui_ths -lmgncs

LIBVDPSKIN=libvdpskin.a
VDPSKIN_INCLUDE=-I./vdpskin
VDPSKIN_LIB=-Lvdpskin -lvdpskin

LOGGING_INCLUDE=-Ilogging
LOGGING_LIB= -Llogging -llogging

DEFINES := -D_MGNCS_RDR_SKIN
INCLUDE := -Iinclude $(VDPSKIN_INCLUDE) $(MINIGUI_INCLUDE) $(LOGGING_INCLUDE)

CPPFLAGS  := -g -O0 -Wall -pthread $(DEFINES) $(INCLUDE)

LDFLAGS := -pthread
#-lts
LIBS    := $(LOGGING_LIB) $(VDPSKIN_LIB) $(MINIGUI_LIB) -lpng -ljpeg -lm -ldl -lfreetype


SOURCE  := $(wildcard src/*.cpp)
OBJS    := $(patsubst %.cpp, %.o, $(SOURCE))

LOGGING = liblogging.a
TARGET := gui

.PHONY : all objs clean rebuild cscope

all : $(TARGET)

objs : $(OBJS)

%.o : %.cpp
	$(C++) $(CPPFLAGS) -c $< -o $@

rebuild : clean all

clean:
	@rm -rf src/*.o
	@rm -rf $(TARGET)
	make -C ./logging clean
	make -C ./vdpskin clean

$(TARGET) : $(OBJS) $(LOGGING) $(LIBVDPSKIN) 
	$(C++) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(LOGGING):
	make -C ./logging

$(LIBVDPSKIN):
	make -C ./vdpskin

cscope:
	@find ./ -name "*.[hc]" > ./cscope.files
	@find ./ -name "*.cpp" >> ./cscope.files
	@cscope -bRqk
	@echo "cscope.files has been updated!"
	@echo ""
