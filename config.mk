# sbase version
VERSION = 0.0

# paths
PREFIX = /usr/local
MANPREFIX = $(PREFIX)/share/man

AR = ar
RANLIB = ranlib

# for NetBSD add -D_NETBSD_SOURCE
# -lrt might be needed on some systems
CPPFLAGS = -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE=700 -D_FILE_OFFSET_BITS=64 -fPIC -static -lrt -Wall
CFLAGS   = -std=c99 -pedantic -Wall -Os -static -fPIC -lrt -static
LDFLAGS  = -s -static
