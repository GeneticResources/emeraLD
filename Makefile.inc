# Makefile that includes this should specify PARENT_MAKE to be
# the Makefile it should include from libStatGen/Makefiles/$(PARENT_MAKE)

# Update version as necessary.
VERSION=0.1

# Check for CXX11
CXX11_AVAIL ?= 1

CPP0X=$(shell if [ $(CCVERSION) \> 4.3.0 ] ; then echo " -std=c++0x" ; fi)

ifeq ($(CXX11_AVAIL), 0)
CPP0X=
endif

########################
# Library Path:
#
# Default path to the statgen library.  You can either update your copy of
# this Makefile to be where you want to get the Makefile from or you can 
# overwrite LIB_PATH_GENERAL or LIB_PATH_EMERALD.
# This design is such that if you have multiple programs, you could just set
# LIB_PATH_GENERAL to the location they should all use to find the library.
# If one program needs a different path, you would set LIB_PATH_EMERALD
# (replacing VERIFY_BAM_ID with the appropriate name) to that different path.
CURRENT_PATH := $(dir $(lastword $(MAKEFILE_LIST)))
LIB_PATH_GENERAL ?= ../libStatGen
LIB_PATH_EMERALD ?= $(LIB_PATH_GENERAL)

# add any additional ../ as necessary if it is a relative path
ACTUAL_PATH = $(if $(filter-out /%,$(LIB_PATH_EMERALD)), \
        $(addprefix $(CURRENT_PATH), $(LIB_PATH_EMERALD)), \
        $(LIB_PATH_EMERALD))
INCLUDE_MAKE = $(ACTUAL_PATH)/Makefiles/$(PARENT_MAKE)

########################
# Include the base Makefile
include $(INCLUDE_MAKE)

.phony: cloneLib

########################
# This is to handle the case where the statgen library is not already there.
# Replace VERIFY_BAM_ID with your your program's name.
$(INCLUDE_MAKE):
	@echo Unable to locate: $(INCLUDE_MAKE)
	@echo To change the location, set LIB_PATH_GENERAL or LIB_PATH_EMERALD to the appropriate path to libStatGen.  Or specify \"make LIB_PATH_GENERAL=yourPath\" or \"make LIB_PATH_EMERALD=yourPath\"
	@echo Use make cloneLib if you have git and want to clone the current libStatGen at that location.


cloneLib:
	@if test -d $(LIB_PATH_EMERALD); \
	then echo $(LIB_PATH_EMERALD) already exists; \
	else git clone git://github.com/statgen/libStatGen.git $(LIB_PATH_EMERALD); fi
	@echo Call make to compile libStatGen and this tool.