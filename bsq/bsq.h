#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>// free

typedef struct s_map
{
	int lines, wc;//how many lines and char per line
	char empty, obstacle, full;
	char **grid;//fill the map
} t_map;
//focus functions->
// calloc, free, fopen, fclose, getline, fprintf

void	ft_bsq_from_stdin(FILE *stream);
void	ft_bsq(char **argv);

#endif