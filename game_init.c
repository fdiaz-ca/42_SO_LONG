/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 06:06:43 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/28 14:17:51 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Draw each element of the map                                              */
static void	ft_draw_map(t_game *game, int x, int y, int *ctrl)
{
	while (y < game->map->n_lines && *ctrl)
	{
		x = 0;
		while (x < game->map->n_colum && *ctrl)
		{
			if (game->map->grid[y][x] == '1')
				*ctrl = mlx_draw_texture(game->img, &(game->wall->texture),
						x * TX_SIZE, y * TX_SIZE);
			else if (game->map->grid[y][x] == 'E')
				*ctrl = mlx_draw_texture(game->img, &(game->exit->texture),
						x * TX_SIZE, y * TX_SIZE);
			else if (game->map->grid[y][x] == 'C')
				*ctrl = mlx_draw_texture(game->img, &(game->collec->texture),
						x * TX_SIZE, y * TX_SIZE);
			else
				*ctrl = mlx_draw_texture(game->img, &(game->floor->texture),
						x * TX_SIZE, y * TX_SIZE);
			x++;
		}
		y++;
	}
}

/* Loads map and opens window's and player's image                           */
static void	ft_draw_game(t_game *game)
{
	int	ctrl;

	ctrl = GOOD;
	game->error = WRONG;
	ft_draw_map(game, 0, 0, &ctrl);
	if (!ctrl)
		return ;
	ctrl = mlx_image_to_window(game->mlx, game->img, 0, 0);
	if (ctrl == -1)
		return ;
	ctrl = mlx_draw_texture(game->pl_img, &(game->pl_tx->texture), 0, 0);
	if (!ctrl)
		return ;
	ctrl = mlx_image_to_window(game->mlx, game->pl_img,
			game->player.x * TX_SIZE, game->player.y * TX_SIZE);
	if (ctrl != -1)
		game->error = GOOD;
}

/* It gives initial value to all variables                                   */
static void	ft_init_values(t_game *game, t_map *map)
{
	game->mlx = NULL;
	game->wall = NULL;
	game->floor = NULL;
	game->collec = NULL;
	game->exit = NULL;
	game->pl_tx = NULL;
	game->img = NULL;
	game->pl_img = NULL;
	game->map = map;
	game->player.x = map->player.x;
	game->player.y = map->player.y;
	game->pl_nxt_mov.x = NOT_YET;
	game->pl_nxt_mov.y = NOT_YET;
	game->mov_cnt = 0;
	game->col_cnt = map->n_collec;
}

/* Set up all variables, checking for errors in the process                  */
static void	ft_init_game(t_game *game, t_map *map)
{
	game->error = WRONG;
	ft_init_values(game, map);
	game->mlx = mlx_init(map->n_colum * TX_SIZE,
			(map->n_lines) * TX_SIZE, "SO_LONG", true);
	if (!game->mlx)
		return ;
	game->img = mlx_new_image(game->mlx, map->n_colum * TX_SIZE,
			map->n_lines * TX_SIZE);
	game->pl_img = mlx_new_image(game->mlx, TX_SIZE, TX_SIZE);
	if (!game->pl_img || !game->img)
		return ;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->wall = mlx_load_xpm42(TX_WALL);
	game->floor = mlx_load_xpm42(TX_FLOOR);
	game->collec = mlx_load_xpm42(TX_COLL);
	game->exit = mlx_load_xpm42(TX_EXIT);
	game->pl_tx = mlx_load_xpm42(TX_PLAYER);
	if (game->wall && game->floor && game->collec && game->exit && game->pl_tx)
		game->error = GOOD;
}

/* Initilizes game structure, calls to draw map and start key hook loop to    */
/* manage game. When finish, it calls game_over to clean up.                  */
void	ft_game_on(t_game *game, t_map *map)
{
	ft_init_game(game, map);
	if (game->error == GOOD)
	{
		ft_draw_game(game);
		mlx_key_hook(game->mlx, pl_hook, game);
		mlx_loop(game->mlx);
	}
	ft_game_over(game);
}
