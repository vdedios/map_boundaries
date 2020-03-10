## map_boundaries
A simple **flood fill algorithm** to check inner map boundaries. Map must be formed by walls (represented as 1), floor (as 0) and player (N, W, E or S). Player must be completelly surrounded by walls in order to consider a valid map

## USAGE
Clone repo and compile the code as follows. You can use maps found in map_samples folder or create yours. Although not mandatory map extension should be ".cub"

`$>gcc -Wall -Werror -Wextra get_next_line.c get_next_line_utils.c map_boundaries.c -o map_boundaries`
`$>./map_boundaries map.cub`
