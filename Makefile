# write by xuwf
TARGET		= main
TARGET_ASM	= main.S
SRCS		= $(wildcard *.cpp *.c)
OBJS		= $(patsubst %.c, %.o, $(patsubst %.cpp, %.o, $(SRCS)))
CC			= gcc
CPP			= gcc
CFLAGS		=
LDFLAG		=
RM			= -rm -rf
DEPEND		= .depend

all:$(DEPEND) $(TARGET)

$(DEPEND):
	@$(CC) -MM $(SRCS) > $(DEPEND)
$(TARGET):$(OBJS)
	$(CPP) -o $@ $(OBJS) $(LDFLAG)

asm:$(TARGET_ASM)
$(TARGET_ASM):$(SRCS)
	$(CC) -o $@ -S $<

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPEND) $(TARGET_ASM)

install:

-include $(DEPEND)
#rules
%.o:%.c
	$(CC) $(CFLAGS) -c $<
%.o:%.cpp
	$(CPP) $(CFLAGS) -c $<
