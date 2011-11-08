/* See LICENSE file for copyright and license details. */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "util.h"

static bool unary(const char *, const char *);
static void usage(void);
static bool binary(const char *, const char *, const char *);

static const char *progname;

int
main(int argc, char *argv[])
{
	bool ret, not = false;

	progname = argv[0];

	/* [ ... ] alias */
	if(!strcmp(argv[0], "[")) {
		if(strcmp(argv[argc-1], "]") != 0)
			usage();
		argc--;
	}
	if(argc > 1 && !strcmp(argv[1], "!")) {
		not = true;
		argv++;
		argc--;
	}
	switch(argc) {
	case 2:
		ret = *argv[1] != '\0';
		break;
	case 3:
		ret = unary(argv[1], argv[2]);
		break;
	case 4:
		ret = binary(argv[1], argv[2], argv[3]);
		break;
	default:
		usage();
	}
	if(not)
		ret = !ret;
	return ret ? EXIT_SUCCESS : EXIT_FAILURE;
}

bool
unary(const char *op, const char *arg)
{
	struct stat st;
	int r;

	if(op[0] != '-' || op[1] == '\0' || op[2] != '\0')
		usage();
	switch(op[1]) {
	case 'b': case 'c': case 'd': case 'e': case 'f':
	case 'g': case 'p': case 'S': case 's': case 'u':
		if((r = stat(arg, &st)) == -1)
			return false; /* -e */
		switch(op[1]) {
		case 'b':
			return S_ISBLK(st.st_mode);
		case 'c':
			return S_ISCHR(st.st_mode);
		case 'd':
			return S_ISDIR(st.st_mode);
		case 'e':
			return true;
		case 'f':
			return S_ISREG(st.st_mode);
		case 'g':
			return st.st_mode & S_ISGID;
		case 'p':
			return S_ISFIFO(st.st_mode);
		case 'S':
			return S_ISSOCK(st.st_mode);
		case 's':
			return st.st_size > 0;
		case 'u':
			return st.st_mode & S_ISUID;
		}
	case 'h': case 'L':
		return lstat(arg, &st) == 0 && S_ISLNK(st.st_mode);
	case 'n':
		return arg[0] != '\0';
	case 't':
		return isatty((int)estrtol(arg, 0));
	case 'r':
		return access(arg, R_OK) == 0;
	case 'w':
		return access(arg, W_OK) == 0;
	case 'x':
		return access(arg, X_OK) == 0;
	case 'z':
		return arg[0] == '\0';
	default:
		usage();
	}
	return false; /* should not reach */
}

void
usage(void)
{
	const char *ket = (progname[0] == '[') ? " ]" : "";

	fprintf(stderr, "usage: %s string%s\n", progname, ket);
	fprintf(stderr, "       %s [!] [-bcdefghLnprSstuwxz] string%s\n",  progname, ket);
	fprintf(stderr, "       %s [!] string1 comparison-op string2%s\n", progname, ket);
	exit(EXIT_FAILURE);
}

bool
binary(const char *arg1, const char *op, const char *arg2)
{
	eprintf("not yet implemented\n");
	return false;
}
