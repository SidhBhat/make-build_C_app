#!/usr/bin/make -f
# Set environment variables

# this makefile follows the below conventions for variables denoting files and directories
# all directory names must end with a terminal '/' character
# file names never end in terminal '/' character


#===================================================
SHELL = /bin/bash

# set this variable to any value to make shared libraries (cleaning existing build files may be necessary)
SHARED =
ifdef SHARED
override SHARED = true
endif

#===================================================
# Compile commands
#===================================================
CC       = gcc
CLIBS    =
CFLAGS   = -g -O -Wall
ifdef SHARED
CFLAGS  += -fpic -fpie
endif
ifneq ($(strip $(filter install install-bin,$(MAKECMDGOALS))),)
RPATH    = $(DESTDIR)$(libdir)
else
RPATH    = $(buildir)
endif
AR       = ar
ARFLAGS  = crs
#======================================================
# Build Directories
#======================================================
override srcdir     = src/
override buildir    = build/
#======================================================
# Install directories
#======================================================
DESTDIR     =
prefix      = /usr/local/
override exec_prefix = $(prefix)
override bindir      = $(exec_prefix)/bin/
override datarootdir = $(prefix)/share/
override datadir     = $(datarootdir)
override libdir      = $(prefix)/lib/
#=======================================================
prog_name = main
#=======================================================
INSTALL          = install -D -p
INSTALL_PROGRAM  = $(INSTALL) -m 755
INSTALL_DATA     = $(INSTALL) -m 644
#=======================================================
#Other files
#=======================================================
override libconfigfile = config.mk
override mainconfig    = libconfig.mk
override timestamp     = timestamp.txt
#updating of COMPLIESTAMP instucts to recompile the executable
override compilestamp  = compilestamp.txt
#=======================================================
# DO NOT MODIFY VARIABLES!
#====================================================
# Source and target objects
#====================================================
#Source files
override SRCS      = $(wildcard $(srcdir)*/*.c)
override MAIN_SRCS = $(wildcard $(srcdir)*.c)
override SRCDIRS   = $(sort $(dir $(SRCS)))
#build objects
override BUILD_DIRS = $(addprefix $(buildir),$(subst $(srcdir),,$(SRCDIRS)))
override OBJS       = $(patsubst %.c,%.c.o,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
override OBJS_S     = $(patsubst %.c,%-shared.c.o,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
#make files for build objects
override MKS       = $(patsubst %.c,%.mk,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
override MKS_S     = $(patsubst %.c,%-shared.mk,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
#Library config files
override LIBCONFS    = $(addsuffix $(libconfigfile),$(SRCDIRS))
override GLOBALCONFS = $(srcdir)$(mainconfig)
#config varaiables
override CLIBS_DEP :=
ifeq ($(strip $(filter generate% remove%,$(MAKECMDGOALS))),) 
# read config variables
-include $(LIBCONFS) $(GLOBALCONFS)
endif
#set the libraries to build 
ifdef SHARED
override LIBS      = $(addprefix $(buildir),$(addsuffix .so,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(BUILD_DIRS))))))
else
ifndef SHAREDCOSTOM
override LIBS      = $(addprefix $(buildir),$(addsuffix .a,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(BUILD_DIRS))))))
endif
endif
#set  C libraries to use while makeing executables
ifndef CLIBS
override CLIBS += -L./$(buildir) $(addprefix -l,$(subst /,,$(subst $(buildir),,$(BUILD_DIRS))))
endif
override CLIBS += $(sort $(CLIBS_DEP))
#=====================================================

build:
.PHONY:build

.DEFUALT_GOAL:build

debug:
	@echo -e "\e[35mBuild Directories \e[0m: $(BUILD_DIRS)"
	@echo -e "\e[35mSource Directories\e[0m: $(SRCDIRS)"
	@echo -e "\e[35mLibconf Files     \e[0m: $(LIBCONFS)"
	@echo -e "\e[35mGlobalconfig File \e[0m: $(GLOBALCONFS)"
	@echo -e "\e[35mLibraries Files   \e[0m: $(LIBS)"
	@echo    "#-------------------------------------------#"
	@echo -e "\e[35mSource Library Files   \e[0m: $(SRCS)"
	@echo -e "\e[35mSource Executable Files\e[0m: $(MAIN_SRCS)"
	@echo -e "\e[35mMake Object Files          \e[0m: $(MKS)"
	@echo -e "\e[35mMake Shared-Object Files   \e[0m: $(MKS_S)"
	@echo -e "\e[35mObject Files           \e[0m: $(OBJS)"
	@echo -e "\e[35mObject Shared Files    \e[0m: $(OBJS_S)"
	@echo -e "\e[35mCMD Goals \e[0m: $(MAKECMDGOALS)"
	@echo -e "\e[35mMakeflags \e[0m: $(MAKEFLAGS)"
	@echo -e "\e[35mClibs     \e[0m: $(CLIBS)"
	@echo -e "\e[35mClibs DEP \e[0m: $(CLIBS_DEP)"
.PHONY:debug

#=====================================================
# export declarations
#============
#target to build executable
#============

#disable builtin rules
.SUFFIXES:

$(buildir)%.mk : $(srcdir)%.c
	@mkdir -p $(@D)
	@$(CC) -M $< -MT $(buildir)$*.c.o | awk '{ print $$0 } END { printf("\t$$(CC) $$(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$$(CFLAGS)) $$(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*.c.o $<\n\ttouch $(@D)/$(timestamp)\n") }' > $@
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

$(buildir)%-shared.mk : $(srcdir)%.c
	@mkdir -p $(@D)
	@$(CC) -M $< -MT $(buildir)$*-shared.c.o | awk '{ print $$0 } END { printf("\t$$(CC) $$(CFLAGS) $$(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*-shared.c.o $<\n\ttouch $(@D)/$(timestamp)\n") }' > $@
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

#=====================================================

hash = \#

create-makes: create-makes-shared create-makes-static
.PHONY:create-makes

create-makes-shared: $(MKS)
.PHONY:create-makes-static

create-makes-static: $(MKS_S)
.PHONY:create-makes

clean:
	rm -rf $(buildir)
.PHONY:clean

clean-all:clean remove-config-files
.PHONY:clean-all

#config files

generate-config-files: generate-libdependancy-config-files generate-testlibconf-file
.PHONY:generate-config-files

generate-testlibconf-file: $(GLOBALCONFS)
.PHONY:generate-testlibconf-file

generate-libdependancy-config-files: $(LIBCONFS)
.PHONY:generate-libdependancy-config-files

ifneq ($(strip $(filter generate% remove%,$(MAKECMDGOALS))),)
$(GLOBALCONFS):
	@echo -e "$(hash)!/usr/bin/make -f"\
	"\n$(hash) Make config file for linker options, do not rename."\
	"\n$(hash) The value of the variable must be LIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\noverride CLIBS += -L./$(buildir) $(addprefix -l,$(subst /,,$(subst $(buildir),,$(BUILD_DIRS))))"\
	"\noverride INCLUDES +=" >  $@

$(srcdir)%/$(libconfigfile):
	@echo -e "$(hash)!/bin/make -f"\
	"\n$(hash) Make config file for library options, do not rename."\
	"\n$(hash) The name of the variable must be CLIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\nCLIBS_$* ="\
	"\nINCLUDES_$* ="\
	"\n$(hash) Set this variable to true if you want a shared library for this variable"\
	"\nSHARED_$* ="\
	"\n$(hash) DO NOT modify below this line unless you know what you are doing.\n"\
	"\noverride CLIBS_DEP += \$$(filter-out \$$(CLIBS),\$$(CLIBS_$*))\n"\
	"\nifndef buildir"\
	"\n\$$(error buildir must be defined)"\
	"\nendif"\
	"\nifneq (\$$(strip \$$(SHARED_$*)),)"\
	"\noverride SHAREDCOSTOM = true"\
	"\noverride LIBS += \$$(buildir)lib$*.so"\
	"\nelse"\
	"\noverride LIBS += \$$(buildir)lib$*.a"\
	"\nendif" > $@
endif

remove-config-files: remove-libdependancy-config-files remove-testlibconf-file
.PHONY:remove-config-files

remove-testlibconf-file:
	rm -f $(GLOBALCONFS) 
.PHONY:generate-testlibconf-file

remove-libdependancy-config-files:
	rm -f $(LIBCONFS)
.PHONY:remove-libdependancy-config-files
