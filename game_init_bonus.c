/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:55:53 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 14:19:43 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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
	ft_draw_map(game, 0, 0, &ctrl);
	if (!ctrl)
		ft_error(game, LD_IMG_ERR, "draw map");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		ft_error(game, LD_IMG_ERR, "game->img to win");
	if ((mlx_image_to_window(game->mlx, game->player->img,
				game->player->pos.x * TX_SIZE,
				game->player->pos.y * TX_SIZE)) < 0)
		ft_error(game, LD_IMG_ERR, "game->player->img");
}

/* It gives initial value to all variables                                   */
static void	ft_init_values(t_game *game, t_map *map)
{
	game->error = GOOD;
	game->mlx = NULL;
	game->wall = NULL;
	game->floor = NULL;
	game->collec = NULL;
	game->exit = NULL;
	game->baddy = NULL;
	game->img = NULL;
	game->txt_img = NULL;
	game->player = NULL;
	game->door = NULL;
	game->dir = 0;
	game->door_cnt = NOT_YET;
	game->pl_cnt = 0;
	game->map = map;
	game->pl_nxt_mov.x = NOT_YET;
	game->pl_nxt_mov.y = NOT_YET;
	game->dead_cnt = NOT_YET;
	game->mov_cnt = 0;
	game->col_cnt = map->n_collec;
	game->baddies = map->baddies;
	game->map->baddies = NULL;
}

/* Set up all variables, checking for errors in the process                  */
static void	ft_init_game(t_game *game, t_map *map)
{
	ft_init_values(game, map);
	game->mlx = mlx_init(map->n_colum * TX_SIZE,
			(map->n_lines + 1) * TX_SIZE, "SO_LONG", true);
	if (!game->mlx)
		ft_error(game, MEM_ERR, "mlx init");
	game->img = mlx_new_image(game->mlx, map->n_colum * TX_SIZE,
			(map->n_lines + 1) * TX_SIZE);
	if (!game->img)
		ft_error(game, MEM_ERR, "img init");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->wall = mlx_load_xpm42(TX_WALL);
	game->floor = mlx_load_xpm42(TX_FLOOR);
	game->collec = mlx_load_xpm42(TX_COLL);
	game->exit = mlx_load_xpm42(TX_EXIT);
	game->baddy = mlx_load_xpm42(TX_BADDY);
	game->player = ft_load_player(game);
	if (!(game->wall && game->floor && game->collec
			&& game->exit && game->player && game->baddy))
		ft_error(game, LD_IMG_ERR, "tx init");
}

/* Initilizes game structure, calls to draw map and baddies, and start loop  */
/* Captain Hook, to manage game. When finish, it calls game_over to clean up.*/
void	ft_game_on(t_game *game, t_map *map)
{
	t_baddies	*baddy;

	ft_init_game(game, map);
	if (game->error == GOOD)
	{
		ft_draw_game(game);
		baddy = game->baddies;
		while (baddy)
		{
			ft_draw_baddy(game, baddy);
			baddy = baddy->next;
		}
		mlx_loop_hook(game->mlx, ft_capt_hook, game);
		mlx_loop(game->mlx);
	}
	ft_game_over(game);
}
