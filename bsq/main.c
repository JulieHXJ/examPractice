// #include "bsq.h"


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>// free

typedef struct s_map
{
	int lines, wc;//how many lines and char per line
	char empty, obstacle, full;
	char **grid;//fill the map
} t_map;


void free_map(t_map *map){
	if (!map)
		return;
	if (map->grid)
	{
		for (int i = 0; i < map->lines; i++)
			free(map->grid[i]);//free the line
		free(map->grid);
		map->grid = NULL;
	}
}

//only read first line of file
//  - The number of lines on the map;
//  - The "empty" character;
//  - The "obstacle" character;
//  - The "full" character.
int parse_header(FILE *file, t_map *map){
	char *line = NULL;
	size_t buf = 0;//capacity for getline, not used
	ssize_t nread;//includes \n, so >= 1
	
	nread = getline(&line, &buf, file);
	if (nread <= 0)
		return -1;//read fail
	if (line[nread - 1] != '\n')
	{
		free(line);//missing \n
		return -1;
	}
	//9 . o x\n
	if (fscanf(&line, "%d %c %c %c", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
	{
		//not 4 parameters
		free(line);
		return -1;
	}
	if (map->lines <= 0)
	{
		free(line);
		return -1;
	}
	if (map->empty == map->full || map->empty == map->obstacle || map->full == map->obstacle)
	{
		free(line);
		return -1;
	}
	free(line);
	return 0;
}


// Definition of a valid map :
//  - All lines must have the same length.
//  - There's at least one line of at least one box.
//  - At each end of line, there's a line break.
//  - The characters on the map can only be those introduced in the first line.
//  - The map is invalid if a character is missing from the first line, or if two characters (of empty, full and obstacle) are identical.
//  - The characters can be any printable character, even numbers.
//  - In case of an invalid map, your program should display "map error" on the error output followed by a line break. Your program will then move on to the next map.
int fill_map(FILE *file, t_map *map){

	//malloc lines
	map->grid = calloc(map->lines, sizeof(char *));
	if (!map->grid)
	{
		return -1;
	}

	//getline
	char *line = NULL;
	size_t buf = 0;
	ssize_t nread;
	
	for (int i = 0; i < map->lines; i++)
	{
		nread = getline(&line, &buf, file);
		if (nread <= 0)
			return -1;

		//check \n and remove
		if (line[nread - 1] != '\n')
			return (free(line), -1);
		line[nread - 1] = '\0';
		nread--;
		
		//init wc with first line and check line length 
		if (i == 0)
		{
			map->wc = nread;
			if (map->wc <= 0)
				return (free(line), -1);
		}else {
			if (nread != map->wc)
				return (free(line), -1);
		}

		//malloc for each line
		map->grid[i] = calloc(map->wc, sizeof(char));//do i need to +1 for wc?
		if (!map->grid[i])
		{
			return (free(line), -1);
		}

		//fill greid and check if only contains empty or obstacle chars
		for (int j = 0; j < nread; j++)
		{
			if (line[j] != map->empty && line[j] != map->obstacle)
			{
				return (free(line), -1);
			}
			map->grid[i][j] = line[j];
		}
		//is \0 needed at the end of each line?

	}	
	free(line);
	return 0;
}

// fputs is safer than fprintf for printing %..
void print_map(t_map *map){
	for (int i = 0; i < map->lines; i++)
	{
		fputs(map->grid[i], stdout);//put string of the line
		fputs("\n", stdout);
	}
}

int contain_ob(t_map *map, int bottom_y, int bottom_x, int size){

	int start_y = bottom_y - size + 1;
	int start_x = bottom_x - size + 1;
	for (int i = start_y; i < bottom_y; i++)
	{
		for (int j = start_x; j < bottom_x; j++)
		{
			if (map->grid[start_y][start_x] == map->obstacle)
			{
				return 1;
			}
			
		}
		
	}
	return 0;
}

//logic: start from top left corner of the square and calculate the size from max possible to 1
void solve_map(t_map *map){

	// the size of the square depends on the shortest distance to edge or obstacle

	int best_size = 0;
	int best_y = 0;
	int best_x = 0;
	int max_possible = 0;

// 找：
// map->best_size
// map->best_top
// map->best_left
// 处理并列 tie-break：先 top 小，再 left 小
	for (int y = 0; y < map->lines; y++)
	{
		for (int x = 0; x < map->wc; x++)
		{
			//the biggest can fit in
			max_possible = (map->wc - x < map->lines - y)? map->wc - x : map->lines - y;

			//try size iter from max_possible to 1
			for (int size = max_possible; size > 0; size--)
			{
				//check obstacles
				if (!contain_ob(map, y, x, size))
				{
					if (size > best_size || (size = best_size && y < best_y) || (size == best_size && y == best_y && x < best_x))
					{
						best_x = x;
						best_y = y;
						best_size = size;
					}
					break;//find the biggset one, break the loop.
				}
			}
		}
	}

	//update grid with full char
	for (int i = best_y; i < best_y + best_size; i++)
	{
		for (int j = best_x; j < best_x + best_size; j++)
		{
			map->grid[i][j] = map->full;
		}
	}
	print_map(map);
}


//read from stdin or argv
void ft_bsq(FILE *file, t_map *map){
	
	if (parse_header(file, map) == -1){
		fprintf(stderr, "map error\n");
		return;
	}
	if (fill_map(file, map) == -1){
		fprintf(stderr, "map error\n");
		free_map(map);
		return;
	}
	solve_map(map);

}

// A file containing the map will be provided. It'll have to be passed as an argument for your program.
// When your program receives more than one map in argument, each solution or "map error" must be followed by a line break.
// Should there be no passed arguments, your program must be able to read on the standard input.
int main(int ac, char **av){

	t_map map = {0};
	if (ac == 1)
	{
		//no file, exit if error
		ft_bsq(stdin, &map);
	}else{
		//multiple maps
		for (int i = 1; i < ac; i++)
		{
			//fopen & fclose
			//FILE *fopen(const char *path, const char *mode);
			FILE *file = fopen(av[i], "r");
			if (!file)
			{
				fprintf(stderr, "map error\n");
				continue;
			}
			ft_bsq(file, &map);
			fclose(file);
			//print "\n"
			if (i < ac - 1)
			{
				fprintf(stdout, "\n");
			}
		}
		
	}
	return 0;
}