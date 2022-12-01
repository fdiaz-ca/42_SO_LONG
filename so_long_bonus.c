/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:31:14 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/28 15:20:28 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Mini function that returns a t_pos variable                               */
t_pos	ft_get_pos(int x, int y)
{
	t_pos	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}

/* It cleans the map structure.                                              */
void	ft_free_map(t_map *map)
{
	int	i;

	if (map)
	{
		if (map->grid)
		{
			i = 0;
			while (map->grid[i])
			{
				free(map->grid[i]);
				i++;
			}
			free(map->grid);
		}
		free(map);
	}
}

/* Print an error message occurred loading the map.                          */
static void	ft_map_error(t_map *map)
{
	if (!map || map->error == MEM_ERR)
	{
		ft_printf("Error\n\nNot enough memmory.\n");
	}
	else if (map->error == LEC_ERR)
	{
		ft_printf("Error\n\nInvalid map. Try again with a valid map.\n");
		ft_printf("Format: <(path/)map's name>.ber\n");
	}
	else if (map->error == WRG_MAP)
	{
		ft_printf("Error\n\nInvalid map. Try again with a valid map.\n\n");
		ft_printf("Need at least 1 exit, 1 collectible, and 1 start point.");
		ft_printf("\nThe map must be rectangular, closed by walls.\n");
		ft_printf("Only these 6 characters: '0', '1', 'E', 'C', 'P', 'B'.\n");
	}
}

/* Print an error message and call the game to clean structures and close up */
void	ft_error(t_game *game, int error, char *str)
{
	(void)str;
	if (error == MEM_ERR)
		ft_printf("Error:\nNot enough memmory\n");
	else if (error == LD_IMG_ERR)
		ft_printf("Error:\nNot loading image");
	game->error = WRONG;
	ft_game_over(game);
	exit(1);
}

/* Reads and loads the map. If it's good, it calls the enviroment to load.   */
int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;
	int		fd;

	fd = 0;
	map = NULL;
	map = ft_init_map(argc, argv, map, fd);
	if (!map || (map->error != GOOD))
	{
		ft_map_error(map);
		ft_free_map(map);
	}
	else
	{
		game = malloc(sizeof(t_game));
		if (!game)
		{
			ft_printf("Memmory error\n");
			ft_free_map(map);
		}
		else
			ft_game_on(game, map);
	}
	return (0);
}
