# -*- Makefile -*- for MingW
# - Install msys2 + mingw
# - Launch the CLI window of msys2
# - Install the mingw tcl and libcurl with pacman
#      Eg. pacman -S mingw64/mingw-w64-x86_64-tcl
#          pacman -S mingw64/mingw-w64-x86_64-curl
# - Go to the location of this file
# - Just type "make" command. 
# - The tclcurl package will be generated in folder: tclcurl$(VERSION).dll 


CC      =gcc
DLLWRAP =dllwrap
DLLTOOL =dlltool
RM      =rm -f
CFLAGS +=$(shell curl-config --cflags)
CFLAGS +=-Wall -O2 -DHAVE_UNISTD_H -DUSE_TCL_STUBS 
LIBS   +=-ltclstub86 $(shell curl-config --static-libs)
LDFLAGS +=-s

VERSION = 7.64.0
DLL     =tclcurl$(VERSION).dll
DEFFILE =tclcurl.def

WRAPFLAGS =--driver-name $(CC) --def $(DEFFILE)
SRCPATH =../../generic

CSRCS   =dllmain.c $(SRCPATH)/tclcurl.c $(SRCPATH)/multi.c
OBJS    =$(CSRCS:.c=.o)

TARGET = tclcurl-$(VERSION)

$(DLL): $(OBJS)
	$(DLLWRAP) $(WRAPFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	$(RM) $(OBJS) $(DLL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

install:
	if [ ! -d $(TARGET) ]; then \
		mkdir $(TARGET); \
	fi
	echo "package ifneeded TclCurl $(VERSION) [list load [file join \$$dir $(DLL)]]\\n[list source [file join \$$dir tclcurl.tcl]]" >$(TARGET)/pkgIndex.tcl
	cp $(SRCPATH)/tclcurl.tcl $(DLL) $(TARGET)

