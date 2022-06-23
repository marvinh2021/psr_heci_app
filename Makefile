########################################################################
############################ Makefile ##################################
########################################################################

LOCAL_PATH := $(strip $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST)))))

# Compiler settings - Can be customized.
AR = ar
CC = gcc
CCXX = g++
AROPS = r
CFLAGS := -g
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lheci_psr

# Makefile settings - Can be customized.
APPNAME = psr_heci_app
C_EXT = .c
CPP_EXT = .cpp
SRCDIR := $(LOCAL_PATH)/src
OBJDIR := $(LOCAL_PATH)/obj
INCLUDEDIR := $(SRCDIR)/include
LIBDIR := $(LOCAL_PATH)
CFLAGS += -I$(INCLUDEDIR)
CXXFLAGS += -I$(INCLUDEDIR)

############## Do not change anything from here downwards! #############
C_SRC := $(wildcard $(SRCDIR)/*$(C_EXT))
CPP_SRC := $(wildcard $(SRCDIR)/*$(CPP_EXT))
C_OBJ := $(C_SRC:$(SRCDIR)/%$(C_EXT)=$(OBJDIR)/%.o)
CPP_OBJ := $(CPP_SRC:$(SRCDIR)/%$(CPP_EXT)=$(OBJDIR)/%.o)
LIBS := $(LIBDIR)/libheci_psr.a
# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(C_OBJ) $(CPP_OBJ)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(APPNAME)

# Builds the app
$(LOCAL_PATH)/$(APPNAME): $(CPP_OBJ) | $(LIBS)
	$(CCXX) $(CXXFLAGS) -o $@ $^ -L$(LIBDIR) $(LDFLAGS)

# Building rule for .a libraries
$(LIBS): $(C_OBJ)
	$(AR) $(AROPS) $@ $^

# Building rule for .o files and its .cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(CPP_EXT)
	$(CCXX) $(CXXFLAGS) -o $@ -c $<

# Building rule for .o files and its .c in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(C_EXT)
	$(CC) $(CFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME) $(LIBS)
