
TARGET := libnavigator.a

CC      := gcc
AR	:= ar
LIBS    :=
LDFLAGS := -pthread

DEFINES := 
INCLUDE := -I. -I../logging -I/usr/local/include/minigui -I/usr/local/include/mgncs
CFLAGS  := -g -O0 -Wall -Wno-pointer-to-int-cast -pthread $(DEFINES) $(INCLUDE)
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H

SRC := $(wildcard *.c)
OBJS:= $(patsubst %.c, %.o, $(SRC))

.PHONY : all objs clean rebuild

all : $(TARGET)

objs : $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

rebuild: clean all

clean :
	@rm -rf *.o
	@rm -rf $(TARGET)
  
$(TARGET) : $(OBJS)
	$(AR) rsv $@ $(OBJS)

