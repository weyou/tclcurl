# -*- Makefile -*- for MinGW
# - Install MSYS2 + MinGW
# - Launch the CLI window of MSYS2. 
#      To build 32bit things, choose MSYS2 MinGW 32-bit 
#      To build 64bit things, choose MSYS2 MinGW 64-bit 
# - Install the MinGW tcl and libcurl with pacman coammnd
#      For 32bit
#      $ pacman -S mingw-w64-i686-tcl
#      $ pacman -S mingw-w64-i686-curl 
#      For 64bit
#      $ pacman -S mingw-w64-x86_64-tcl
#      $ pacman -S mingw-w64-x86_64-curl
#   The libcurl installation is just for installing the dependent libraries
#   We don't need the libcurl from pacman, will built it as a STATIC lib
#   from source.
# - Download libcurl source from https://curl.haxx.se/download.html and build:
#		$ ./buildconf
#		$ CPPFLAGS="-DNGHTTP2_STATICLIB" LDFLAGS="-static" PKG_CONFIG="pkg-config --static" ./configure --enable-static --disable-shared --without-brotli ...
#       $ make curl_LDFLAGS=-all-static V=1
#		# make curl_LDFLAGS=-all-static install V=1
# - Go to the location of this file
# - Just type "make" command. 
# - The TclCurl package will be generated in folder: tclcurl$(VERSION).dll 


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

