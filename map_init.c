/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:01:28 by pakismac          #+#    #+#             */
/*   Updated: 2022/11/28 15:06:19 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* It valids a wall line, depending on its position in the map               */
static int	ft_good_wall(t_map *map, int y)
{
	int	x;

	if ((y == 0) || (y == map->n_lines - 1))
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] != '1')
				return (WRONG);
			x++;
		}
	}
	else if (map->grid[y][0] != '1' || map->grid[y][map->n_colum - 1] != '1')
		return (WRONG);
	return (GOOD);
}

/* It checks wall structure and lenth of lines, and checks if map has        */
/* valids elements on it. Get position of player, sets door as closed, and   */
/* increases collectibles counter if it's found.                             */
static int	ft_check_map(t_map *map, int x, int y)
{
	while (map->grid[y])
	{
		if ((int)ft_strlen(map->grid[y]) != map->n_colum
			|| !ft_good_wall(map, y))
			return (WRONG);
		else
		{
			x = 0;
			while (map->grid[y][x])
			{
				if (map->grid[y][x] == 'C')
					map->n_collec += 1;
				else if (map->grid[y][x] == 'E' && map->exit == NOT_YET)
					map->exit = 0;
				else if (map->grid[y][x] == 'P' && map->player.x == NOT_YET)
					ft_player_pos(map, x, y);
				else if ((map->grid[y][x] != '1') && (map->grid[y][x] != '0'))
					return (WRONG);
				x++;
			}
		}
		y++;
	}
	return (GOOD);
}

/* It checks if file has ".ber" extension, if file can be opened, and counts */
/* number of lines in file. Then closes-opens file to set fd at beggening.   */
static int	ft_good_name(char *name, int *fd, t_map *map)
{
	int		len;
	char	*str;

	len = (int)ft_strlen(name);
	if (!ft_strncmp(name + (len - 4), ".ber", 4))
	{
		*fd = open(name, O_RDONLY);
		if (*fd != -1)
		{
			map->n_lines = 0;
			str = get_next_line(*fd);
			while (str)
			{
				map->n_lines += 1;
				free(str);
				str = get_next_line(*fd);
			}
			close(*fd);
			*fd = open(name, O_RDONLY);
			if (*fd != -1)
				return (GOOD);
		}
	}
	return (LEC_ERR);
}

/* Reads map file, saves each line in map structure. Then checks if it's ok. */
static void	ft_get_grid(t_map *map, int fd)
{
	char	*str;
	int		i;

	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (str[(int)ft_strlen(str) - 1] == '\n')
			str[(int)ft_strlen(str) - 1] = '\0';
		map->grid[i] = str;
		str = get_next_line(fd);
		i++;
	}
	map->n_colum = (int)ft_strlen(map->grid[0]);
	if (ft_check_map(map, 0, 0) == WRONG
		|| map->n_collec < 1 || map->exit == NOT_YET
		|| map->player.x == NOT_YET)
		map->error = WRG_MAP;
}

/* If passed argument is a good name, it initializes map structure,          */
/* and reads the map's grid.                                                 */
t_map	*ft_init_map(int argc, char **argv)
{
	t_map	*map;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (map && (argc == 2) && (ft_good_name(argv[1], &fd, map) == GOOD))
	{
		map->n_collec = 0;
		map->exit = NOT_YET;
		map->player.x = NOT_YET;
		map->player.y = NOT_YET;
		map->error = GOOD;
		map->grid = calloc(sizeof(char *), map->n_lines + 1);
		if (!map->grid)
			map->error = MEM_ERR;
		else
			ft_get_grid(map, fd);
		close(fd);
	}
	else if (map)
	{
		map->error = LEC_ERR;
		map->grid = NULL;
	}
	return (map);
}
