# File: Makefile
# Author: Paul Lin 
# Mailto: paul415236@gmail.com
# Date: Jul.24 2017

#################
#	 modes	#
#################

#################
#	target	#
#################
TARGET = out

#################
#	env	#
#################
PWD = $(shell pwd)

#################
#	srcs	#
#################
#SRC := $(foreach sdir,$(PWD),$(wildcard $(sdir)/*.c))
SRC = $(PWD)/main.c \
	$(PWD)/common.c

OBJ := $(patsubst $(PWD)/%.c,$(PWD)/%.o,$(SRC))
DIR_INC := $(addprefix -I,$(PWD))

#########################
#	toolchain	#
#########################
CROSS_TOOL = 
CC = gcc
STRIP = strip
CXX = g++
AR = ar

#########################
#	INCs & LIBs	#
#########################
INC = -I$(PWD)
INC += -I/usr/local/include

LIB = -L$(PWD)
LIB += -L/usr/local/lib

#################
#	FLAGS	#
#################
CFLAGS = -std=c11
CFLAGS += -O2
CFLAGS += -Wall
#CFLAGS += -g
#CFLAGS += -Q
#CFLAGS += -v
#CFLAGS += -da

LFLAGS = -lpthread

vpath %.c $(PWD)

.PHONY: clean

%.o: %.c
	@echo "\033[32m [CC] $@ \033[0m"
	@$(CC) $(CFLAGS) $(LFLAGS) -o $@ -c $< $(INC) $(LIB)

all: clean $(OBJ)
	@$(CC) $(OBJ) -o $(TARGET) $(CFLAGS) $(LFLAGS) $(INC) $(LIB)
	@echo "\033[32m [STRIP] $(TARGET) \033[0m"
	@$(STRIP) $(TARGET)

clean:
	rm -f $(PWD)/*.o
	rm -f $(TARGET)
