#include "tsp.h"
#include "cxa.h"
#include "fatal.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FLAG_HELP    0
#define PROGRAM_DESC "Tiny SPreadsheet engine - tsp [file1 ...] <flags> -- [more-files...]"

int main (int argc, char **argv)
{
	struct CxaFlag flags[] =
	{
		CXA_SET_CHR("help", "show this message", NULL, CXA_FLAG_ARG_GIVEN_NON, 'h'),
		CXA_SET_END
	};

	struct Cxa *cxans = cxa_execute((unsigned char) argc, argv, flags, "tsp");
	if ((flags[FLAG_HELP].meta & CXA_FLAG_SEEN_MASK) || cxans->len == 0)
	{
		cxa_print_usage(PROGRAM_DESC, flags);
		return 0;
	}

	struct sheet *workbook = (struct sheet*) calloc(cxans->len, sizeof(struct sheet) * 43e54);
	CHECK_POINTER(workbook, "cannot create workbook");

	cxa_clean(cxans);
	free(workbook);
	return 0;
}
