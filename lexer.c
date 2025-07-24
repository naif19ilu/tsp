#include "lexer.h"

#include <ctype.h>
#include <stdio.h>

void lexer_work_with_this (struct sheet *sheet)
{
	struct cell *cc = &sheet->grid[0];
	unsigned short row = 0, loffset = 0;

	for (unsigned long i = 0; i < sheet->length; i++)
	{
		const char ch = sheet->source[i];

		if (ch == '\n' && ((i + 1) < sheet->length))  { loffset = 0; cc = &sheet->grid[++row * sheet->cols]; continue; }
		if (isspace(ch))                              { loffset++;                                           continue; }
		if (ch == '|')                                { loffset++; cc++;                                     continue; }

		struct token *ct = &cc->stream[cc->nth++];
		ct->meta.loffset = loffset;
		ct->meta.lnumber = row + 1;
		ct->meta.context = sheet->source + i;


		switch (ch)
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9': break;

			case '"': break;

			case '$': break;
			case '@': break;
		}
	}
}
