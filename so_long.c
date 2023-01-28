/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 20:31:14 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2023/01/28 13:31:25 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Mini function that sets t_pos variable                                    */
void	ft_player_pos(t_map *map, int x, int y)
{
	map->player.x = x;
	map->player.y = y;
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
		ft_printf("Only these 5 characters: '0', '1', 'E', 'C', 'P'.\n");
	}
}

/* Reads and loads the map. If it's good, it calls the enviroment to load.   */
int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	map = ft_init_map(argc, argv);
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
