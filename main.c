#include "cxa.h"
#include "fatal.h"
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define FLAG_HELP    0
#define PROGRAM_DESC "Tiny SPreadsheet engine - tsp [file1 ...] <flags> -- [more-files...]"

static void init_sheet (const char*, struct sheet*);
static void build_sheet (struct sheet*);

int main (int argc, char **argv)
{
	struct CxaFlag flags[] =
	{
		CXA_SET_CHR("help", "show this message", NULL, CXA_FLAG_ARG_GIVEN_NON, 'h'),
		CXA_SET_END
	};

	struct Cxa *cxans = cxa_execute((unsigned char) argc, argv, flags, "tsp");
	const unsigned long sheetsgiven = cxans->len;

	if ((flags[FLAG_HELP].meta & CXA_FLAG_SEEN_MASK) || sheetsgiven == 0)
	{
		cxa_print_usage(PROGRAM_DESC, flags);
		return 0;
	}

	struct sheet *workbook = (struct sheet*) calloc(sheetsgiven, sizeof(struct sheet));
	CHECK_POINTER(workbook, "cannot create workbook");

	for (unsigned long i = 0; i < sheetsgiven; i++) { init_sheet(cxans->positional[i], &workbook[i]); }
	cxa_clean(cxans);

	for (unsigned long n = 0; n < sheetsgiven; n++) { lexer_work_with_this(&workbook[n]); }
	return 0;
}

static void init_sheet (const char *filename, struct sheet *sheet)
{
	sheet->path = filename;
	FILE *file = fopen(filename, "r");

	if (!file) { fatal_file_ops(filename); }

	fseek(file, 0, SEEK_END);
	sheet->length = ftell(file);
	fseek(file, 0, SEEK_SET);

	sheet->source = (char*) calloc(sheet->length + 1, sizeof(char));
	CHECK_POINTER(sheet->source, "cannot reserve space for reading sheet");

	fread(sheet->source, 1, sheet->length, file);
	if (ferror(file)) { fatal_file_ops(filename); }
	if (fclose(file)) { fatal_file_ops(filename); }

	build_sheet(sheet);
}

static void build_sheet (struct sheet *sheet)
{
	unsigned short auxcol = 0;

	for (unsigned long i = 0; i < sheet->length; i++)
	{
		switch (sheet->source[i])
		{
			case '|': { auxcol++; break; }
			case '\n':
			{
				sheet->cols = (sheet->cols > auxcol) ? sheet->cols : auxcol;
				sheet->rows++;
				auxcol = 0;
				break;
			}
		}
	}

	sheet->cols = (sheet->cols > auxcol) ? sheet->cols : auxcol;
	sheet->noCells = sheet->rows * sheet->cols;

	sheet->grid = (struct cell*) calloc(sheet->noCells, sizeof(struct cell));
	CHECK_POINTER(sheet->grid, "cannot reserve space for grid");
}
