APP = demo
PLATFORM = linux
DEBUG = y
PROGRAM = bcstack
TRANSPORT = usb

CC = gcc
LD = gcc

SRCS = \
	$(wildcard apps/$(APP)/*.c) \
	$(wildcard platform/$(PLATFORM)/*.c) \
	$(wildcard bluetooth/utils/*.c) \
	$(wildcard bluetooth/stack/hci/*.c) \
	$(wildcard bluetooth/stack/hci/$(TRANSPORT)/*.c) \
	$(wildcard bluetooth/stack/l2cap/*.c) \
	$(wildcard bluetooth/stack/sdp/*.c) \
	$(wildcard bluetooth/stack/rfcomm/*.c) \
	$(wildcard bluetooth/stack/vport/*.c) \
	$(wildcard bluetooth/stack/gatt/*.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -I./bluetooth/include
LDFLAGS =

ifeq ($(DEBUG),y)
CFLAGS += -DDEBUG=1 -g
endif

ifeq ($(TRANSPORT),usb)
CFLAGS += `pkg-config libusb-1.0 --cflags` -DUSE_LIBUSB=1 -DINIT_CMD_NUM=1
LDFLAGS += `pkg-config libusb-1.0 --libs`
endif

ifeq ($(TRANSPORT),bcsp)
CFLAGS += -DUSE_BTUART=1 -DINIT_CMD_NUM=0
endif

ifeq ($(TRANSPORT),null)
CFLAGS += -DINIT_CMD_NUM=1
endif

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LD) $(OBJS) -o $(PROGRAM) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(PROGRAM)
