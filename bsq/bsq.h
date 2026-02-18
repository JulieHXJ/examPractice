#ifndef BSQ_H
# define BSQ_H

#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

typedef struct s_map
{
	int lines, wc;
	char empty, obstacle, full;
	char** grid;
}t_map;


void ft_bsq(FILE *file);
void free_map(t_map *map);
void print_map(t_map *map);

int parse_header(FILE *file, t_map *map);//validation: check number of chars, printable & duplication
int fill_map(FILE *file, t_map *map);//validation: check len of each line
void solve_map(t_map *map);//solve top left from biggest to smallest









#endif