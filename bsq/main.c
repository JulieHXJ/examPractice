// #include "bsq.h"

// A file containing the map will be provided. It'll have to be passed as an argument for your program.
// When your program receives more than one map in argument, each solution or "map error" must be followed by a line break.
// Should there be no passed arguments, your program must be able to read on the standard input.






int main(int ac, char **av){

	if (ac == 1)
	{
		//no file
		ft_bsq_from_stdin(stdin);
	}else{
		ft_bsq(av[1]);
	}
	
}