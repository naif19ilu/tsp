#include "lexer.h"
#include "fatal.h"

#include <float.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

struct lexer
{
	unsigned long  at;
	unsigned short loffset;
};

static void extract_literal_number (struct token*, struct lexer*);
static void extract_literal_string (struct token*, struct lexer*);

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
		ct->type         = (enum token_type) ch;

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

			case '-': if (isdigit(sheet->source[lxr.at + 1])) extract_literal_number(ct, &lxr); break;

			case '"': extract_literal_string(ct, &lxr); break;

			case '$': break;
			case '@': break;

			default: break;
		}
	}
}

static void extract_literal_number (struct token *token, struct lexer *lxr)
{
	char *fini;
	token->as.number = strtold(token->meta.context, &fini);

	const unsigned int diff = fini - token->meta.context;
	if (token->as.number >= LDBL_MAX || token->as.number <= LDBL_MIN)
	{
		fatal_pre_lexer(token->meta.context, (unsigned short) diff, token->meta.lnumber, token->meta.loffset, prelex_number_overflow);
	}

	lxr->at      += diff;
	lxr->loffset += diff;

	token->type = token_is_number;
	printf("(%d, %d): number: %Lf\n", token->meta.lnumber, token->meta.loffset, token->as.number);
}

static void extract_literal_string (struct token *token, struct lexer *lxr)
{
	token->as.text = 0;
	char *src = token->meta.context + 1;

	while (src[token->as.text] != '"')
	{
		if (src[token->as.text] == 0)
		{
			fatal_pre_lexer(token->meta.context, token->as.text, token->meta.lnumber, token->meta.loffset, prelex_nontermiated_string);
		}
		token->as.text++;
	}

	printf("(%d, %d): string: %.*s\n", token->as.text, token->meta.loffset, (int) token->as.text, src);
	token->type = token_is_string;

	lxr->at      += token->as.text + 1;
	lxr->loffset += token->as.text + 1;
}
