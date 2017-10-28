EXE	:= ketm
BLD_DBG := YES
RM	:= rm -f
MKDIR   := mkdir -p
BLDD    := build
COUNTER := $(BLDD)/.cnt.sh
JUNK    := $(shell find . -name '*~')
SRCS	:= src
SOURCES	:= $(SRCS) include
OBJS    := $(foreach dir, $(SOURCES),   $(patsubst $(dir)/%.c,  $(BLDD)/%.o,$(wildcard $(dir)/*.c)))
SRCFILES:= $(foreach dir, $(SOURCES), $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.h))
SHOW_BLD = printf "[%3d%%] \033[32mBuilding file \033[1m%s\033[0m\n"  `$(COUNTER)`
SHOW_LNK = printf "[%3d%%] \033[34mLinking binary \033[34;1m%s\033[0m\n"  `$(COUNTER)`
SHOW_SUCESS  = printf "[%3d%%] \033[33;1mSuccessfully build target \033[0;33m%s\033[0m\n"  `$(COUNTER)`


ifeq ($(BLD_DBG), YES)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -03
endif
# Add SDL dependency
LDFLAGS +=$(shell sdl-config --libs) -lSDL_gfx -lSDL_image -lpng -lSDL_mixer -lm
CFLAGS +=$(shell sdl-config --cflags) -Iinclude

all : $(BLDD) $(COUNTER) $(EXE)
edit:
	@$(LEDITOR) Makefile $(SRCFILES) >/dev/null 2>&1 &

$(COUNTER): Makefile $(BLDD)
	@echo "#!/bin/sh">$@
	@echo 'expr 100 "*" `ls -1d $(BLDD)/*.o $(EXE) 2>/dev/null|wc -l` "/" `echo $(OBJS) $(EXE)|wc -w`' >> $@
	@chmod 700 $@

$(BLDD):
	@$(MKDIR) $(BLDD)

$(BLDD)/%.o: $(SRCS)/%.c include/*.h
	@$(SHOW_BLD) $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(EXE) : $(BLDD) $(COUNTER) $(OBJS)
	@$(SHOW_LNK) $@
	@$(CC) $(OBJS) -o $(EXE) $(LDFLAGS)

clean:
	@$(RM) $(OBJS) $(EXE) $(JUNK) $(BLDD)/.cnt.sh
	@$(RM) -r $(BLDD)

.PHONY:clean all edit
.PRECIOUS: $(OBJS)
.SUFFIXES: .o .c .h .S .cpp
