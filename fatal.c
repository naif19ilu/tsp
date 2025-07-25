#include "fatal.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

/* 'strerrordesc_np' function returns in fact a string
 * but gcc does not recognize it so better redefine the
 * defintion
 */
const char* strerrordesc_np(int);

void fatal_file_ops (const char *filename)
{
	const char *const fmt =
	"tsp:\x1b[31mfatal:\x1b[0m cannot continue due to file issues\n"
	"  reason: %s\n"
	"  file  : %s\n"
	"  aborting now!\n";
	fprintf(stderr, fmt, strerrordesc_np(errno), filename);
	exit(EXIT_FAILURE);
}

void fatal_memory_ops (const char *desc)
{
	const char *const fmt =
	"tsp:\x1b[31mfatal:\x1b[0m cannot continue due to memory management issues\n"
	"  reason: %s\n"
	"  while : %s\n"
	"  aborting now!\n";
	fprintf(stderr, fmt, strerrordesc_np(errno), desc);
	exit(EXIT_FAILURE);
}

void fatal_pre_lexer (const char *context, const unsigned short length, const unsigned short lnum, const unsigned short loff, const enum pre_lexer_err why)
{
	static const char *const errors[] =
	{
		"number-overflow!",
		"non-terminated-string"
	};

	static const char *const template =
	  "tsp:\x1b[31mfatal:\x1b[0mlexer: cannot continue due to %s error\n"
	  "  token can be found on %d line with an offset of %d\n"
	  "  %-5d  %.*s\n         \x1b[31m";

	fprintf(stderr, template, errors[why], lnum, loff, lnum, length, context);
	for (unsigned short i = 0; i < length; i++)
	{
		fputc('~', stderr);
	}
	fprintf(stderr, "\n\x1b[0m");
	exit(EXIT_FAILURE);
}
