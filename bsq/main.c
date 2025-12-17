#include "bsq.h"



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
	if (nread == -1 || line[nread - 1] != "\n")
	{
		//EOF or error or missing \n
		return -1;
	}
	//9 . o x\n
	if (fscanf(&line, "%d %c %c %c", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
	{
		//not 4 parameters
		fprintf(stdout, "map error\n");
		return -1;
	}
	if (map->lines <= 0)
	{
		fprintf(stdout, "map error\n");
		return -1;
	}
	if (map->empty == map->full || map->empty == map->obstacle || map->full == map->obstacle)
	{
		fprintf(stdout, "map error\n");
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

	map->grid = calloc(map->lines, sizeof(char *));
	for (int i = 0; i < map->lines; i++)
	{
		map->grid[i] = calloc(map->wc, sizeof(char));
	}

	
	
	while (getline())
	{
		/* code */
	}
	

	//early return
	// exit 1;

}


void print_map(t_map *map){

}

int solve_map(t_map *map){



	print_map(map);
}


//read from stdin or argv
void ft_bsq(FILE *file, t_map *map){

	parse_header(file, map);//print map error
	fill_map(file, map);
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