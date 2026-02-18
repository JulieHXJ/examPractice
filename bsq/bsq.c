#include "bsq.h"

void free_map(t_map *map){
	if(!map || !map->grid){
		return;
	}
	for (int i = 0; i < map->lines; i++)
	{
		free(map->grid[i]);
	}
	free(map->grid);
	map->grid = NULL;//!!
}

// fputs is safer than fprintf for printing %..
void print_map(t_map *map){
	for (int i = 0; i < map->lines; i++)
	{
		fputs(map->grid[i], stdout);
		fputs("\n", stdout);
	}
}

//only read first line of file 用 fscanf 读 4 个字段，再用 getline 吃掉 header 行剩余部分
//  - The number of lines on the map;
//  - The "empty" character;
//  - The "obstacle" character;
//  - The "full" character.
int parse_header(FILE *file, t_map *map){
	if (fscanf(file, "%d %c %c %c", &map->lines, &map->empty, &map->obstacle, &map->full) != 4)
		return -1;//not 4 parameters
	else if (map->lines <= 0)
		return -1;
	else if (map->empty < 32 || map->empty > 126)
		return -1;//not printable
	else if (map->obstacle < 32 || map->obstacle > 126)
		return -1;
	else if (map->full < 32 || map->full > 126)
		return -1;
	else if (map->empty == map->full || map->empty == map->obstacle || map->full == map->obstacle)
		return -1;

	// 吃掉 header 行剩余内容（包括 '\n'）
	char    *rest = NULL;
    size_t   cap = 0;
    ssize_t  n;
	n = getline(&rest, &cap, file);
	if (n == -1)
		return -1;
	free(rest);
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
	// fprintf(stderr, "empty=%c obstacle=%c full=%c\n",
    //     map->empty, map->obstacle, map->full);
	map->wc = 0;
	map->grid = calloc(map->lines, sizeof(char *));
	if (!map->grid)
		return -1;
	
	//getline
	char *line = NULL;
	size_t buf = 0;
	ssize_t nread = 0;
	for (int i = 0; i < map->lines; i++)
	{
		nread = getline(&line, &buf, file);
		if (nread <= 0 || line[nread - 1] != '\n')
			return (free(line), -1);
		
		line[nread - 1] = '\0';//remove \n
		nread--;
		
		//init wc with first line and check each line length 
		if (i == 0)
		{
			map->wc = nread;
			if (map->wc <= 0)
				return (free(line), -1);
		}else{
			if (nread != map->wc)
				return (free(line), -1);
		}

		map->grid[i] = calloc(map->wc + 1, sizeof(char));// +1 for \0
		if (!map->grid[i])
			return (free(line), -1);
		
		//fill grid and check if only contains empty or obstacle chars
		for (int j = 0; j < map->wc; j++)
		{
			if (line[j] != map->empty && line[j] != map->obstacle)
				return (free(line), -1);
			map->grid[i][j] = line[j];
		}
		
		
	}
	free(line);
	return 0;
}

//check the square contains obstacle or not
int contain_ob(t_map* map, int top_x, int top_y, int size){

	int bottom_x = top_x + size;
	int bottom_y = top_y + size;
	for (int i = top_y; i < bottom_y; i++)
	{
		for (int j = top_x; j < bottom_x; j++)
		{
			if (map->grid[i][j] == map->obstacle)
				return 1;
		}
	}
	return 0;
}


//logic: start from top left corner of the square and calculate the size from max possible to 1
// the size of the square depends on the shortest distance to edge or obstacle
void solve_map(t_map* map){
	int best_size = 0;
	int best_x = 0;//top left x of the square
	int best_y = 0;//top left y
	int max_possible = 0;

	for (int y = 0; y < map->lines; y++)
	{
		for (int x = 0; x < map->wc; x++)
		{
			int max_x = map->wc - x;
			int max_y = map->lines - y;
			max_possible = (max_x < max_y)? max_x : max_y; // assume the biggest square can fit in to the edge

			//try size from max to 1
			for (int size = max_possible; 0 < size; size--)
			{
				if (!contain_ob(map, x, y, size))
				{
					if (size > best_size)
					{
						best_size = size;
						best_x = x;
						best_y = y;
					}
					break;//find the max, break the loop
				}
				
			}
			
		}
		
	}

	//replace the empty with full char
	for (int i = best_y; i < best_y + best_size; i++)
	{
		for (int j = best_x; j < best_x + best_size; j++)
			map->grid[i][j] = map->full;
	}
}


void ft_bsq(FILE *file){
	t_map *map = calloc(1, sizeof(t_map));// malloc and free() for each map file

	if (parse_header(file, map) == -1){
		fprintf(stderr, "map error2\n");
		free(map);//!
		return;
	}
	if (fill_map(file, map) == -1)
	{
		fprintf(stderr, "map error3\n");
		free_map(map);
		free(map);//!
		return;
	}
	solve_map(map);
	print_map(map);
	free_map(map);
	free(map);//!
}

// A file containing the map will be provided. It'll have to be passed as an argument for your program.
// When your program receives more than one map in argument, each solution or "map error" must be followed by a line break.
// Should there be no passed arguments, your program must be able to read on the standard input.
int main(int ac, char** av){
	if (ac < 2)
	{
		ft_bsq(stdin);
	}else{
		for(int i = 1; i < ac; i++){
			FILE *file = fopen(av[i], "r");//FILE *fopen(const char *path, const char *mode);
			if (file)
			{
				ft_bsq(file);
				fclose(file);//fopen & fclose
			} else{
				fprintf(stderr, "map error1\n");// file read failure also need to print error!
			}
			if (i < ac - 1)
					fprintf(stdout, "\n");//print "\n" after each map
		}
	}
	return 0;
}