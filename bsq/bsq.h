#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>// free
#include <stdbool.h>// for bool

//全局变量，在解析地图时赋值一次
	extern ssize_t		map_array;//地图行数
	extern char		    empty;//.
	extern char		    obstacle;//o
	extern char	    	full;//替换字符


//focus functions->
// calloc, free, fopen, fclose, getline, fprintf

void	ft_bsq_from_stdin(FILE *stream);
void	ft_bsq(char **argv);
