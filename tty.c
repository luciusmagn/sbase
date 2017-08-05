/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <unistd.h>

#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *tty;

	argv0 = *argv, argv0 ? (argc--, argv++) : (void *)0;

	if (argc)
		usage();

	tty = ttyname(STDIN_FILENO);
	puts(tty ? tty : "not a tty");

	return fshut(stdout, "<stdout>") || !tty;
}
