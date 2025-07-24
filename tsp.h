#ifndef TSP_H
#define TSP_H

#define CHECK_POINTER(ptr, a)    do { if (ptr) break; fatal_memory_ops(a); } while (0)

enum cell_type
{
	cell_is_empty = 0,
	cell_is_text,
	cell_is_number,
	cell_is_error
};

struct cell
{
	union
	{
		char        *error;
		long double number;
		struct      { char *source; unsigned long length; } text;
	} as;
	enum cell_type type;
};

struct sheet
{
	struct cell  *grid;
	char         *path;
	unsigned int rows, cols, cells;
};

#endif
