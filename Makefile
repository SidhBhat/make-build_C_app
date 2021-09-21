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
SHARED = true
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
override INSTALL          = install -D -p
override INSTALL_PROGRAM  = $(INSTALL) -m 755
override INSTALL_DATA     = $(INSTALL) -m 644
#=======================================================
#Other files
#=======================================================
override LIBCONFIGFILE = config.mk
override MAINCONFIG    = libconfig.mk
override TIMESTAMP     = timestamp.txt
#updating of COMPLIESTAMP instucts to recompile the file
override COMPILESTAMP  = compilestamp.txt
#=======================================================
# DO NOT MODIFY VARIABLES!
#====================================================
# Source and target objects
#====================================================
SRCS      = $(wildcard $(srcdir)*/*.c)
MAIN_SRCS = $(wildcard $(srcdir)*.c)
DIRS      = $(addprefix $(buildir),$(subst $(srcdir),,$(SRCDIRS)))
SRCDIRS   = $(sort $(dir $(SRCS)))
OBJS      = $(patsubst %.c,%.c.o,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
OBJS_S    = $(patsubst %.c,%-shared.c.o,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
MKS       = $(patsubst %.c,%.mk,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
MKS_S     = $(patsubst %.c,%-shared.mk,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
override CLIBS_DEP :=
LIBCONFS  = $(addsuffix $(LIBCONFIGFILE),$(SRCDIRS))
ifeq ($(strip $(filter generate% remove%,$(MAKECMDGOALS))),) 
-include $(LIBCONFS)
endif
ifdef SHARED
LIBS      = $(addprefix $(buildir),$(addsuffix .so,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(DIRS))))))
else
ifndef SHAREDCOSTOM
LIBS      = $(addprefix $(buildir),$(addsuffix .a,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(DIRS))))))
endif
endif
#=====================================================

build: $(LIBS)
.PHONY:build

.DEFUALT_GOAL:build

install: install-libs install-bin
.PHONY: install

install-libs: LIB_FILES = $(addprefix $(DESTDIR)$(libdir),$(notdir $(LIBS)))
install-libs: build
	@for file in $(LIB_FILES); do \
		[ -f "$$file" ] && { echo -e "\e[31mError\e[32m $$file exists Defualt behavior is not to overwrite...\e[0m Terminating..."; exit 23; } || true; \
	done
ifndef SHARED
	$(INSTALL_DATA) $(LIBS) -t $(DESTDIR)$(libdir)
else
	$(INSTALL_PROGRAM) $(LIBS) -t $(DESTDIR)$(libdir)
endif
.PHONY: install

install-bin: test
	@[ -f "$(DESTDIR)$(bindir)$(prog_name)" ] && { echo -e "\e[31mError\e[32m $$file exists Defualt behavior is not to overwrite...\e[0m Terminating..."; exit 24; } || true
	$(INSTALL_PROGRAM) $(buildir)$(prog_name) -t $(DESTDIR)$(bindir)
.PHONY:install-bin

#phony to go in install mode
installmode:
	rm -f $(buildir)$(COMPILESTAMP)
.PHONY:installmode

debug:
	@echo -e "\e[35mBuild Directories \e[0m: $(DIRS)"
	@echo -e "\e[35mSource Directories\e[0m: $(SRCDIRS)"
	@echo -e "\e[35mLibdepconf Files  \e[0m: $(LIBCONFS)"
	@echo -e "\e[35mBuild Files       \e[0m: $(LIBS)"
	@echo    "#-------------------------------------------#"
	@echo -e "\e[35mSource Files     \e[0m: $(SRCS) $(MAIN_SRCS)"
	@echo -e "\e[35mMake Files       \e[0m: $(MKS)"
	@echo -e "\e[35mMake Files Shared\e[0m: $(MKS_S)"	
	@echo -e "\e[35mObject Files     \e[0m: $(OBJS)"
.PHONY:debug

help:
	@echo "The follwing targets may be given..."
	@echo -e "\t...install"
	@echo -e "\t...install-bin"
	@echo -e "\t...install-libs"
	@echo -e "\t...build*"
	@echo -e "\t...test"
	@echo -e "\t...uninstall"
	@echo -e "\t...uninstall-bin"
	@echo -e "\t...uninstall-libs"
	@echo -e "\t...clean"
	@echo -e "\t...clean-all"
	@echo "Other options"
	@echo -e "\t...debug"
	@echo -e "\t...help"
	@echo -e "\t...generate-config-file"
	@echo -e "\t...remove-config-file"
.PHONY: help

test: $(buildir)$(prog_name)
.PHONY:test

build-obj: build-obj-static build-obj-shared ;
.PHONY: build-obj

build-obj-static: $(OBJS)
.PHONY:build-obj-static

build-obj-shared: $(OBJS_S)
.PHONY:build-obj-shared

ifeq ($(strip $(filter generate% remove%,$(MAKECMDGOALS))),)
-include $(srcdir)$(MAINCONFIG)
endif

#=====================================================
ifndef CLIBS
override CLIBS += -L./$(buildir) $(addprefix -l,$(subst /,,$(subst $(buildir),,$(DIRS))))
endif
override CLIBS += $(sort $(CLIBS_DEP))

export CC CFLAGS INCLUDES RPATH CLIBS
export INSTALL INSTALL_DATA INSTALL_PROGRAM
export buildir srcdir
export prog_name
export SHARED
#============
ifdef SHAREDCOSTOM
$(buildir)$(prog_name): export SHARED = true
endif
ifneq ($(strip $(filter install install-bin,$(MAKECMDGOALS))),)
export override INSTALLMODE = true
$(buildir)$(prog_name) : $(LIBS) installmode $(MAIN_SRCS)
else
export override INSTALLMODE =
$(buildir)$(prog_name): COMPILESTAMP_TMP = $(buildir)$(COMPILESTAMP) $(addsuffix $(TIMESTAMP),$(DIRS))
$(buildir)$(prog_name): $(LIBS) $(buildir)$(COMPILESTAMP) $(MAIN_SRCS)
endif
	$(MAKE) -e -f Makefile2 $(patsubst INSTALLSTAMP=%,,$(MAKEFLAGS)) COMPILESTAMP="$(COMPILESTAMP_TMP)"

$(buildir)$(COMPILESTAMP): $(LIBS)
	touch $@

#============

$(buildir)%.mk : $(srcdir)%.c
	@mkdir -p $(@D)
	@$(CC) -M $< -MT $(buildir)$*.c.o | awk '{ print $$0 } END { printf("\t$(CC) $(filter-out -pie -fpie -Fpie,$(CFLAGS)) $(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*.c.o $<\n\ttouch $(@D)/$(TIMESTAMP)\n") }' > $@
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

$(buildir)%-shared.mk : $(srcdir)%.c
	@mkdir -p $(@D)
	@$(CC) -M $< -MT $(buildir)$*-shared.c.o | awk '{ print $$0 } END { printf("\t$(CC) $(CFLAGS) $(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*-shared.c.o $<\n\ttouch $(@D)/$(TIMESTAMP)\n") }' > $@
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

ifdef SHARED
MAKE_BUILD_FILES=$(MKS_S)
else
ifndef SHAREDCOSTOM
MAKE_BUILD_FILES=$(MKS)
else
MAKE_BUILD_FILES=$(MKS)	$(MKS_S)
endif
endif

ifneq ($(strip $(filter build build-obj test install install-bin install-libs install $(buildir)$(prog_name) $(LIBS) $(OBJS),$(MAKECMDGOALS))),)
include $(MAKE_BUILD_FILES)
else ifeq ($(MAKECMDGOALS),)
include $(MAKE_BUILD_FILES)
endif

lib%.a: %/$(TIMESTAMP) | $(buildir)
	$(AR) $(ARFLAGS) $@ $(filter $*/%.o,$(OBJS)) $(if $(CLIBS_$(notdir $*)),-l"$(strip $(CLIBS_$(notdir $*)))")
lib%.so: %/$(TIMESTAMP) | $(buildir)
	$(CC) $(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$(CFLAGS)) --shared $(filter $*/%.o,$(OBJS_S)) $(strip $(CLIBS_$(notdir $*))) -o $@

%/$(TIMESTAMP): $(buildir) ;

.SECONDARY: $(addsuffix $(TIMESTAMP),$(DIRS))

ifdef SHARED
$(buildir): build-obj-shared ;
else
ifndef SHAREDCOSTOM
$(buildir) : build-obj-static ;
else
$(buildir) : build-obj-static build-obj-shared;
endif
endif

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

#use with caution!
uninstall-libs:
	rm -f $(addprefix $(DESTDIR)$(libdir),$(notdir $(LIBS)))
.PHONY:uninstall-libs

#use with caution!
uninstall-bin:
	rm -f $(DESTDIR)$(bindir)$(prog_name)
.PHONY:uninstall-bin

#use with caution!
uninstall:uninstall-bin uninstall-libs
.PHONY:uninstall

generate-config-files: generate-libdependancy-config-files generate-testlibconf-file
.PHONY:generate-config-files

remove-config-files: remove-libdependancy-config-files remove-testlibconf-file
.PHONY:remove-config-files

generate-testlibconf-file: $(srcdir)$(MAINCONFIG)
.PHONY:generate-testlibconf-file

generate-libdependancy-config-files: $(LIBCONFS)
.PHONY:generate-libdependancy-config-files

ifneq ($(strip $(filter generate% remove%,$(MAKECMDGOALS))),)
$(srcdir)$(MAINCONFIG):
	@echo -e "$(hash)!/usr/bin/make -f"\
	"\n$(hash) Make config file for linker options, do not rename."\
	"\n$(hash) The value of the variable must be LIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\noverride CLIBS += -L./$(buildir) $(addprefix -l,$(subst /,,$(subst $(buildir),,$(DIRS))))"\
	"\noverride INCLUDES +=" >  $@

$(srcdir)%/$(LIBCONFIGFILE):
	@echo -e "$(hash)!/bin/make -f"\
	"\n$(hash) Make config file for library options, do not rename."\
	"\n$(hash) The name of the variable must be CLIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\nCLIBS_$* ="\
	"\nINCLUDES_$* ="\
	"\n$(hash) Set this variable to true if you want a shared library for this variable"\
	"\nSHARED_$* ="\
	"\n$(hash) DO NOT modify below this line unless you know what you are doing.\n"\
	"\nCLIBS_DEP += \$$(filter-out \$$(CLIBS),\$$(CLIBS_$*))\n"\
	"\nifndef buildir"\
	"\n\$$(error buildir must be defined)"\
	"\nendif"\
	"\nifneq (\$$(strip \$$(SHARED_$*)),)"\
	"\nSHAREDCOSTOM = true"\
	"\nLIBS += \$$(buildir)lib$*.so"\
	"\nelse"\
	"\nLIBS += \$$(buildir)lib$*.a"\
	"\nendif" > $@
endif

remove-testlibconf-file:
	rm -f $(srcdir)$(MAINCONFIG)
.PHONY:generate-testlibconf-file

remove-libdependancy-config-files:
	rm -f $(LIBCONFS)
.PHONY:remove-libdependancy-config-files
