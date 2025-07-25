#ifndef TSP_FATAL_H
#define TSP_FATAL_H

enum pre_lexer_err
{
	prelex_number_overflow = 0,
	prelex_nontermiated_string,
};

void fatal_file_ops (const char*);
void fatal_memory_ops (const char*);

void fatal_pre_lexer (const char*, const unsigned short, const unsigned short, const unsigned short, const enum pre_lexer_err);

#endif
