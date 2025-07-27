#ifndef TSP_H
#define TSP_H

#define CHECK_POINTER(ptr, a)   do { if (ptr) break; fatal_memory_ops(a); } while (0)
#define TOKEN_STREAM_LENGTH     64

enum cell_type
{
	cell_is_empty = 0,
	cell_is_text,
	cell_is_number,
	cell_is_error
};

enum token_type
{
	token_is_number,
	token_is_string  = '"',
	token_is_abs_ref = '$',
	token_is_rel_ref = '@',
};

struct cell;

struct token
{
	struct
	{
		unsigned short lnumber, loffset;
		char *context;
	} meta;
	union
	{
		long double    number;
		unsigned short text;
		struct         { struct cell *at; unsigned short row, col, sheetId; } reference;
	} as;
	enum token_type type;
};

struct cell
{
	union
	{
		char        *error;
		long double number;
		struct      { char *source; unsigned long length; } text;
	} as;

	struct token   stream[TOKEN_STREAM_LENGTH];
	unsigned short nth;
	enum cell_type type;
};

struct sheet
{
	struct cell    *grid;
	const char     *path;
	char           *source;
	unsigned long  length, noCells;
	unsigned short rows, cols;
	unsigned short id;
};

struct engine
{
	struct
	{
		unsigned short precision;
	} args;
	struct sheet   *workbook;
	unsigned short workbooksz;
};

#endif
