#include "lexer.h"

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct lexer
{
	unsigned long  at;
	unsigned short loffset;
};

static void extract_literal_number (struct token*, struct lexer*);

void lexer_workout (struct sheet *sheet)
{
	struct cell *cc = &sheet->grid[0];
	unsigned short row = 0;

	struct lexer lxr = {0, 0};

	for (; lxr.at < sheet->length; lxr.at++)
	{
		const char ch = sheet->source[lxr.at];

		if (ch == '\n' && ((lxr.at + 1) < sheet->length)) { lxr.loffset = 0; cc = &sheet->grid[++row * sheet->cols]; continue; }
		if (isspace(ch))                                  { lxr.loffset++;                                           continue; }
		if (ch == '|')                                    { lxr.loffset++; cc++;                                     continue; }

		struct token *ct = &cc->stream[cc->nth++];
		ct->meta.loffset = lxr.loffset++;
		ct->meta.lnumber = row + 1;
		ct->meta.context = sheet->source + lxr.at;

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
			case '9': extract_literal_number(ct, &lxr); break;

			case '"': break;

			case '$': break;
			case '@': break;
		}
	}
}

static void extract_literal_number (struct token *token, struct lexer *lxr)
{
	char *fini;
	errno = 0;

	token->as.number = strtold(token->meta.context, &fini);
	if (errno == ERANGE)
	{
	}

	const unsigned int diff = fini - token->meta.context;
	lxr->at      += diff;
	lxr->loffset += diff;

	token->type = token_is_number;
	printf("(%d, %d): number: %Lf\n", token->meta.lnumber, token->meta.loffset, token->as.number);
}
