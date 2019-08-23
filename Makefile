C++ := g++
AR  := ar

MINIGUI_INCLUDE=-I/usr/local/include/minigui
MINIGUI_LIB=-L/usr/local/lib -lminigui_ths -lmgncs -lmgncs4touch -lmgeff  

LIBNAVIGATOR=libnavigator.a
NAVIGATOR_INCLUDE=-I./navigator
NAVIGATOR_LIB=-L./navigator -lnavigator

LIBVDPSKIN=libvdpskin.a
VDPSKIN_INCLUDE=-I./vdpskin
VDPSKIN_LIB=-Lvdpskin -lvdpskin

LOGGING_INCLUDE=-Ilogging
LOGGING_LIB= -L./logging -llogging

DEFINES := -D_MGNCS_RDR_SKIN
# $(VDPSKIN_INCLUDE) 
INCLUDE := -Iinclude $(NAVIGATOR_INCLUDE) $(MINIGUI_INCLUDE) $(LOGGING_INCLUDE)

CPPFLAGS  := -g -O0 -Wall -pthread $(DEFINES) $(INCLUDE)

LDFLAGS := -pthread
#-lts $(VDPSKIN_LIB)
LIBS    := $(LOGGING_LIB) $(NAVIGATOR_LIB) $(MINIGUI_LIB) -lpng -ljpeg -lm -ldl -lfreetype


SOURCE  := $(wildcard src/*.cpp)
OBJS    := $(patsubst %.cpp, %.o, $(SOURCE))

LOGGING = liblogging.a
TARGET := gui

.PHONY : all objs clean rebuild cscope install

all : $(TARGET)

objs : $(OBJS)

%.o : %.cpp
	$(C++) $(CPPFLAGS) -c $< -o $@

rebuild : clean all

clean:
	@rm -rf src/*.o
	@rm -rf $(TARGET)
	make -C ./logging clean
#	make -C ./vdpskin clean
	make -C ./navigator clean

#$(LIBVDPSKIN)
$(TARGET) : $(OBJS) $(LOGGING) $(LIBNAVIGATOR)
	$(C++) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

$(LOGGING):
	make -C ./logging

$(LIBVDPSKIN):
	make -C ./vdpskin

$(LIBNAVIGATOR):
	make -C ./navigator

cscope:
	@find ./ -name "*.[hc]" > ./cscope.files
	@find ./ -name "*.cpp" >> ./cscope.files
	@cscope -bRqk
	@echo "cscope.files has been updated!"
	@echo ""

install:
	sudo mv /usr/local/etc/mgncs.cfg /usr/local/etc/mgncs.cfg.bak
	sudo cp ./etc/mgncs.cfg /usr/local/etc/
	sudo cp ./res/bkg.gif /usr/local/share/minigui/res/bmp/
