#include "bsq.h"

// Definition of a valid map :
//  - All lines must have the same length.
//  - There's at least one line of at least one box.
//  - At each end of line, there's a line break.
//  - The characters on the map can only be those introduced in the first line.
//  - The map is invalid if a character is missing from the first line, or if two characters (of empty, full and obstacle) are identical.
//  - The characters can be any printable character, even numbers.
//  - In case of an invalid map, your program should display "map error" on the error output followed by a line break. Your program will then move on to the next map.



// 直接从文件解析第一行（更简单的方法）
int parse_header(FILE *file, Map *map)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, file) <= 0)
        return -1;

    int line_len = strlen(line);
    if (line[line_len - 1] == '\n') {
        line[line_len - 1] = '\0';
        line_len--;
    }
    if (line_len < 4)
        return (free(line), -1);
    map->full = line[line_len - 1];
    map->obstacle = line[line_len - 2];
    map->empty = line[line_len - 3];

    // 检查字符重复
    if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
        return (free(line), -1);

    // 手动解析数字（简化版）
    map->rows = 0;
    for (int i = 0; i < line_len - 3; i++)
    {
        if (line[i] >= '0' && line[i] <= '9')
            map->rows = map->rows * 10 + (line[i] - '0');
        else
            return (free(line), -1);
    }
    free(line);
    return (map->rows > 0) ? 0 : -1;
}

// read first line
// map allocation
int read_map(FILE *file, Map *map) {

    if (parse_header(file, map) != 0)
        return -1;

    // 分配网格内存
    map->grid = malloc(map->rows * sizeof(char*));
    if (!map->grid)
        return -1;

    char *line = NULL;
    size_t len = 0;

    // 读取地图行: line is a temporary buffer. ultimate is map->grid[i]
    for (int i = 0; i < map->rows; i++)
    {
        if (getline(&line, &len, file) <= 0)
            return (free(line), -1);

        // 去掉换行符
        int line_len = strlen(line);
        if (line[line_len - 1] == '\n')
        {
            line[line_len - 1] = '\0';
            line_len--;
        }

        // 设置或检查列数
        if (i == 0)
        {
            map->cols = line_len;
            if (map->cols <= 0)
                return (free(line), -1);
        } else if (line_len != map->cols)
            return (free(line), -1);

        // malloc map->cols
        map->grid[i] = malloc(map->cols + 1); //C 语言中，sizeof(char) 永远等于 1。
        if (!map->grid[i])
            return (free(line), -1);

        // 复制并验证字符
        //The map is made up of '"empty" characters', lines and '"obstacle" characters'.
        for (int j = 0; j < map->cols; j++)
        {
            map->grid[i][j] = line[j];
            if (line[j] != map->empty && line[j] != map->obstacle)
                return (free(line), -1);
        }
        map->grid[i][map->cols] = '\0';
    }

    free(line);
    return 0;
}

// 检查从(x,y)开始的size×size正方形是否有障碍
int has_obstacle(Map *map, int y, int x, int size)
{
    for (int i = y; i < y + size; i++)
    {
        for (int j = x; j < x + size; j++)
        {
            if (map->grid[i][j] == map->obstacle)
            {
                return 1;
            }
        }
    }
    return 0;
}

// big loop has an internal smaller loop
void solve_and_print(Map *map)
{
    int best_size = 0, best_x = 0, best_y = 0, max_possible;

    // 通过遍历每个点来寻找最大正方形：找到max possible，然后再确认
    for (int y = 0; y < map->rows; y++) //y represents row
    {
        for (int x = 0; x < map->cols; x++) //x represents column
        {
            if (map->rows - y < map->cols - x) // 选择较小的边界作为最大可能大小
                max_possible = map->rows - y;
            else
                max_possible = map->cols - x;
            for (int size = 1; size <= max_possible; size++)
            {
                if (has_obstacle(map, y, x, size))
                    break;
                if (size > best_size)
                {
                    best_size = size;
                    best_x = x;
                    best_y = y;
                }
            }
        }
    }
    // from best_x and best_y , fill the grid
    for (int i = best_y; i < best_y + best_size; i++)
    {
        for (int j = best_x; j < best_x + best_size; j++)
        {
            map->grid[i][j] = map->full;
        }
    }

    // 打印结果, row by row
    for (int i = 0; i < map->rows; i++) {
        fputs(map->grid[i], stdout);
        fputs("\n", stdout);  // 使用fputs替代printf:fputs 完全不关心字符串里有什么。即使里面全是 %，它也只是原样打印出来。
        //这对于打印来源不确定的原始内容（比如用户输入的地图）是非常安全的
    }
}

//带 s (string) 的是打印字符串的：fputs, puts。
//带 c (char) 的是打印单个字符的：fputc, putc, putchar。
//带 f (file) 的可以指定输出位置 (如 stdout, stderr 或文件指针)。
//不带 f 的默认都输出到标准输出 stdout。

// free array actually
void free_map(Map *map)
{
    if (map->grid)
    {
        for (int i = 0; i < map->rows; i++)
        {
            free(map->grid[i]);
        }
        free(map->grid);
    }
}

// 3 steps: read map from stdin or file.
// solve:
// free: need a pointer because need to free the substance
int process_file(FILE *file)
{
    Map map = {0}; // 经典的 C 语言初始化技巧，叫做 “零初始化” (Zero Initialization)
    //当你用大括号 {} 初始化结构体时，如果你只提供了部分成员的初始值（这里你只提供了第一个成员的值为 0），
    //编译器会自动把剩余的所有成员都初始化为零。如果你只写 Map map; 而不加 = {0}：
    //是更现代、更安全、更简洁的 memset 替代品，专用于初始化阶段。
    if (read_map(file, &map) != 0)
    {
        fprintf(stderr, "map error\n");
        return (free_map(&map), -1);
    }
    solve_and_print(&map);
    free_map(&map);
    return 0;
}

int main(int argc, char **argv) {
    if (argc == 1)
        process_file(stdin);
    else
    {
        for (int i = 1; i < argc; i++)
        {
            FILE *file = fopen(argv[i], "r");
            if (!file)
            {
                fprintf(stderr, "map error\n");
                continue; // need to support multiple maps
            }
            process_file(file);
            fclose(file);
            if (i < argc - 1)
                fputs("\n", stdout);  // 使用fputs替代printf
        }
    }
    return 0;
}