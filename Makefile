#!/usr/bin/make -f
# Set environment variables

# this makefile follows the below conventions for variables denoting files and directories
# all directory names must end with a terminal '/' character
# file names never end in terminal '/' character


#===================================================
SHELL = /bin/bash

# set this variable to any value to make shared libraries (cleaning existing build files may be necessary)
SHARED =

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
#existance of file INSTALLSTAMP instructs to go in non-installmode
override INSTALLSTAMP  = installstamp.txt
#=======================================================
# DO NOT MODIFY VARIABLES!
#====================================================
# Source and target objects
#====================================================
SRCS      = $(wildcard $(srcdir)*/*.c)
DIRS      = $(addprefix $(buildir),$(subst $(srcdir),,$(SRCDIRS)))
SRCDIRS   = $(sort $(dir $(SRCS)))
OBJS      = $(patsubst %.c,%.o,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
MKS       = $(patsubst %.c,%.mk,$(addprefix $(buildir),$(subst $(srcdir),,$(SRCS))))
ifndef SHARED
LIBS      = $(addprefix $(buildir),$(addsuffix .a,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(DIRS))))))
else
LIBS      = $(addprefix $(buildir),$(addsuffix .so,$(addprefix lib,$(subst /,,$(subst $(buildir),,$(DIRS))))))
endif
LIBCONFS  = $(addsuffix $(LIBCONFIGFILE),$(SRCDIRS))
CLIBS_DEP :=
-include $(LIBCONFS)
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
	rm -f $(buildir)$(INSTALLSTAMP)
.PHONY:installmode

debug:
	@echo -e "\e[35mBuild Directories \e[0m: $(DIRS)"
	@echo -e "\e[35mSource Directories\e[0m: $(SRCDIRS)"
	@echo -e "\e[35mLibdepconf Files  \e[0m: $(LIBCONFS)"
	@echo -e "\e[35mBuild Files       \e[0m: $(LIBS)"
	@echo    "#-------------------------------------------#"
	@echo -e "\e[35mSource Files     \e[0m: $(SRCS)"
	@echo -e "\e[35mMake Files       \e[0m: $(MKS)"
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

build-obj: $(OBJS)
.PHONY:build-obj

-include $(srcdir)$(MAINCONFIG)

export CC CFLAGS INCLUDES RPATH CLIBS
export INSTALL INSTALL_DATA INSTALL_PROGRAM
export buildir srcdir
export prog_name
export SHARED
#=====================================================

ifndef CLIBS
ifdef SHARED
CLIBS = -L./$(buildir) $(addprefix -l,$(patsubst $(buildir)lib%.so,%,$(LIBS)))
else
CLIBS = -L./$(buildir) $(addprefix -l,$(patsubst $(buildir)lib%.a,%,$(LIBS)))
endif
endif
CLIBS += $(sort $(CLIBS_DEP))

#============
ifneq ($(strip $(filter install install-bin,$(MAKECMDGOALS))),)
export override INSTALLMODE = true
$(buildir)$(prog_name) : $(LIBS) installmode
else
export override INSTALLMODE =
$(buildir)$(prog_name): INSTALLSTAMP_TMP = $(buildir)$(INSTALLSTAMP)
$(buildir)$(prog_name): $(LIBS) $(buildir)$(INSTALLSTAMP)
endif
	$(MAKE) -e -f Makefile2 $(patsubst INSTALLSTAMP=%,,$(MAKEFLAGS)) INSTALLSTAMP="$(INSTALLSTAMP_TMP)"

$(buildir)$(INSTALLSTAMP):
	touch $@
#============

$(buildir)%.mk : $(srcdir)%.c
	@mkdir -p $(@D)
ifndef SHARED
	@$(CC) -M $< | awk '{ if(/^$(subst .mk,,$(@F))/) { printf("%s%s\n","$(@D)/",$$0) } else { print $$0 } } END { printf("\t$(CC) $(CFLAGS) $(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*.o $<\n\ttouch $(@D)/$(TIMESTAMP)")}' > $@
else
	@$(CC) -M $< | awk '{ if(/^$(subst .mk,,$(@F))/) { printf("%s%s\n","$(@D)/",$$0) } else { print $$0 } } END { printf("\t$(CC) $(filter-out -pie -fpie -Fpie,$(CFLAGS)) $(INCLUDES_$(subst /,,$(dir $*))) -c -o $(buildir)$*.o $<\n\ttouch $(@D)/$(TIMESTAMP)")}' > $@
endif
	@echo -e "\e[32mCreating Makefile \"$@\"\e[0m..."

ifneq ($(strip $(filter build build-obj test install install-bin install-libs install $(buildir)$(prog_name) $(LIBS) $(OBJS),$(MAKECMDGOALS))),)
include $(MKS)
else ifeq ($(MAKECMDGOALS),)
include $(MKS)
endif

ifndef SHARED
lib%.a: %/$(TIMESTAMP) | $(buildir)
	$(AR) $(ARFLAGS) $@ $(filter $*/%.o,$(OBJS)) $(if $(CLIBS_$(notdir $*)),-l"$(strip $(CLIBS_$(notdir $*)))")
else
lib%.so: %/$(TIMESTAMP) | $(buildir)
	$(CC) $(filter-out -pie -fpie -Fpie -pic -fpic -Fpic,$(CFLAGS)) --shared $(filter $*/%.o,$(OBJS)) $(strip $(CLIBS_$(notdir $*))) -o $@
endif

%/$(TIMESTAMP): $(buildir) ;

.SECONDARY: $(addsuffix $(TIMESTAMP),$(DIRS))

$(buildir): build-obj ;

#=====================================================

hash = \#

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

generate-testlibconf-file:
ifndef SHARED
	@echo -e "$(hash)!/usr/bin/make -f"\
	"\n$(hash) Make config file for linker options, do not rename."\
	"\n$(hash) The value of the variable must be LIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\nCLIBS = -L./$(buildir) $(addprefix -l,$(patsubst $(buildir)lib%.a,%,$(LIBS)))"\
	"\nINCLUDES =" > "$(srcdir)$(MAINCONFIG)"
else
	@echo -e "$(hash)!/usr/bin/make -f"\
	"\n$(hash) Make config file for linker options, do not rename."\
	"\n$(hash) The value of the variable must be LIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
	"\nCLIBS = -L./$(buildir) $(addprefix -l,$(patsubst $(buildir)lib%.so,%,$(LIBS)))"\
	"\nINCLUDES =" > "$(srcdir)$(MAINCONFIG)"
endif
.PHONY:generate-testlibconf-file

remove-testlibconf-file:
	rm -f $(srcdir)libconfig.mk
.PHONY:generate-testlibconf-file

generate-libdependancy-config-files:
	@for file in $(LIBCONFS); do \
		stem="$${file%/*}" ; \
		stem="$${stem//$(srcdir)/}" ; \
		stem="$${stem//\//}" ; \
		echo -e "$(hash)!/usr/bin/make -f"\
		"\n$(hash) Make config file for linker options, do not rename."\
		"\n$(hash) The value of the variable must be LIBS_<libname>, where the libname is the stem of lib*.a, for it to be read by the makefile."\
		"\nCLIBS_$${stem} ="\
		"\nINCLUDES_$${stem} ="\
		"\nCLIBS_DEP += \$$(filter-out \$$(CLIBS),\$$(CLIBS_$${stem}))\n" > "$$file"; \
	done
.PHONY:generate-libdependancy-config-files

remove-libdependancy-config-files:
	rm -f $(LIBCONFS)
.PHONY:remove-libdependancy-config-files
