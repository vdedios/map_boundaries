/* 
 * Copyright (c) 2020 Victor Dedios.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "get_next_line.h"

#define GRN "\e[0;32m"
#define YLL "\e[0;33m"
#define RED "\e[0;31m"
#define RST "\e[0m"

/*
 ** Flood fill recursive algorithm
 ** This implementation checks if a player (represented by N) is correctly
 ** surrounded by walls (1) in a map with floor (0)
 */

int		ft_count_lines(char **argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	//Not the most efficient but the fastes to implement
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		free(line);
		i++;
	}
	free(line);
	close (fd);
	return (i);
}

char	**ft_save_map(int i, char **argv)
{
	int		fd;
	char	**map;
	//Saving lines in a 2D array
	if (!(map = malloc((i + 2) * sizeof(char *))))
		return (0);
	i = 0;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &map[i]) > 0)
	{
		i++;
	}
	close (fd);
	map[i + 1] = NULL;
	return (map);
}

int		ft_find_player_pos(int *i, int *j, char **map)
{
	*i = 0;
	*j = 0;
	while (map[*i])
	{
		while (map[*i][*j])
		{
			if (map[*i][*j] == 'N' || map[*i][*j] == 'S' ||
					map[*i][*j] == 'E' || map[*i][*j] == 'W')
				return (1);
			*j = *j + 1;
		}
		*j = 0;
		*i = *i + 1;
	}
	perror("Not player found :(	");
	exit(EXIT_FAILURE);
	return (0);
}

void	ft_printmap(char **map, int ok)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map[i]) 
	{
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
					map[i][j] == 'E' || map[i][j] == 'W')
				printf(YLL "%c" RST, map[i][j]);
			else if (map[i][j] == '5')
			{
				if (ok)
					printf(GRN "%c" RST, map[i][j]);
				else if (!ok)
					printf(RED "%c" RST, map[i][j]);
			}
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

int		ft_flood_fill(char **map, int i, int j, int lines)
{
	if (i && j)
	{
		if((map[i - 1][j] == ' ' && map[i + 1][j] == ' ')
				|| (map[i][j + 1] == ' ' && map[i][j - 1] == ' '))
		{
			ft_printmap(map, 0);
			perror("Wrong map :(	");
			exit(EXIT_FAILURE);
		}
	}
	if ((i < 0) || !map[i][j]  || (j < 0) ||(i == lines))
	{
		ft_printmap(map, 0);
		perror("Wrong map :(	");
		exit(EXIT_FAILURE);
	}
	else if (map[i][j] != '0')
		return (1);
	//This part is not not necessary, just changing values for testing
	map[i][j] = '5';
	ft_flood_fill(map, i + 1, j, lines);
	ft_flood_fill(map, i - 1, j, lines);
	ft_flood_fill(map, i, j + 1, lines);
	ft_flood_fill(map, i, j - 1, lines);
	return (1);
}

int main(int argc, char **argv)
{
	char	**map;
	int		lines;
	int		i;
	int		j;
	(void)  argc;

	if (argc != 2)
	{
		perror("invalid map	");
		exit(EXIT_FAILURE);
	}
	lines = ft_count_lines(argv);
	map = ft_save_map(lines, argv);
	ft_find_player_pos(&i, &j, map);
	printf("----------ORIGINAL MAP---------\n");
	ft_printmap(map, 1);
	map[i][j] = '0';
	printf("----------CALCULATED MAP---------\n");
	ft_flood_fill(map, i, j, lines);
	ft_printmap(map, 1);
	printf("Right map!\n");
	return (0);
}
