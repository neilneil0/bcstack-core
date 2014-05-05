APP = none
PLATFORM = linux
DEBUG = y
PROGRAM = bcstack
TRANSPORT = usb
CPU=generic32
HOST = y

CC = gcc
LD = gcc

SRCS = \
	$(wildcard apps/$(APP)/*.c) \
	$(wildcard platform/$(PLATFORM)/*.c) \
	$(wildcard utils/*.c)

ifeq ($(HOST),y)
SRCS += \
	$(wildcard bluetooth/host/gap/*.c) \
	$(wildcard bluetooth/host/hci/*.c) \
	$(wildcard bluetooth/host/hci/$(TRANSPORT)/*.c) \
	$(wildcard bluetooth/host/server/*.c)
endif

OBJS = $(SRCS:.c=.o)

CFLAGS = -I./include -I./include/cpu/$(CPU)
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

.PHONY: all clean

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LD) $(OBJS) -o $(PROGRAM) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f $(OBJS) $(PROGRAM)
