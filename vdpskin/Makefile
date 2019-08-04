
TARGET := libvdpskin.a

CC      := gcc
AR	:= ar
LIBS    :=
LDFLAGS := -pthread

DEFINES := 
INCLUDE := -I. -I/usr/local/include/minigui -I/usr/local/include/mgncs
CFLAGS  := -g -Wall -Wno-pointer-to-int-cast -pthread $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H

SKINSRC := $(wildcard *.c)
SKINOBJS:= $(patsubst %.c, %.o, $(SKINSRC))

.PHONY : all objs clean rebuild

all : $(TARGET)

objs : $(SKINOBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

clean :
	@rm -fr *.o
	@rm $(TARGET)
  
$(TARGET) : $(SKINOBJS)
	$(AR) rsv $@ $(SKINOBJS)

