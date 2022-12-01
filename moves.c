/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 13:30:42 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/23 15:25:21 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Sets up next position, depending in actual position and passed direction. */
static void	ft_set_next_move(t_game *game, int move)
{
	if (move == RIGHT)
	{
		game->pl_nxt_mov.x = game->player.x + 1;
		game->pl_nxt_mov.y = game->player.y;
	}
	else if (move == LEFT)
	{
		game->pl_nxt_mov.x = game->player.x - 1;
		game->pl_nxt_mov.y = game->player.y;
	}
	else if (move == UP)
	{
		game->pl_nxt_mov.x = game->player.x;
		game->pl_nxt_mov.y = game->player.y - 1;
	}
	else if (move == DOWN)
	{
		game->pl_nxt_mov.x = game->player.x;
		game->pl_nxt_mov.y = game->player.y + 1;
	}
}

/* Depending on direction passed as argument, it changes player position     */
/* values and move also player_image position on window.                     */
static void	ft_player_moves(t_game *game, int move)
{
	if (move == UP)
	{
		game->pl_img->instances[0].y -= TX_SIZE;
		game->player.y -= 1;
	}
	if (move == DOWN)
	{
		game->pl_img->instances[0].y += TX_SIZE;
		game->player.y += 1;
	}
	if (move == LEFT)
	{
		game->pl_img->instances[0].x -= TX_SIZE;
		game->player.x -= 1;
	}
	if (move == RIGHT)
	{
		game->pl_img->instances[0].x += TX_SIZE;
		game->player.x += 1;
	}
	game->mov_cnt += 1;
	ft_printf("Total Moves = %i\n", game->mov_cnt);
}

/* Delete collectable element from map, loads a floor texture instead,       */
/* decreases collected_counter.                                              */
static void	ft_player_collects(t_game *game)
{
	game->col_cnt -= 1;
	game->map->grid[game->player.y][game->player.x] = '0';
	if (!mlx_draw_texture(game->img, &(game->floor->texture),
			game->player.x * TX_SIZE, game->player.y * TX_SIZE))
		game->error = WRONG;
}

/* Checks if next move is a valid one. If it is, and it's not a wall, it     */
/* calls to move player. In new position, check for collectible and exit in  */
/* end of game situation.                                                    */
static void	ft_player_action(t_game *game, int move)
{
	ft_set_next_move(game, move);
	if (game->map->grid[game->pl_nxt_mov.y][game->pl_nxt_mov.x] != '1')
	{
		ft_player_moves(game, move);
		if (game->map->grid[game->player.y][game->player.x] == 'C')
			ft_player_collects(game);
		if ((game->map->grid[game->player.y][game->player.x] == 'E')
				&& (game->col_cnt == 0))
			game->error = WIN;
	}
}

/* Key hook to manage game. Reads key pressed and selects action             */
void	pl_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->error == WIN)
		mlx_close_window(game->mlx);
	if ((keydata.action == MLX_PRESS) || (keydata.action == MLX_REPEAT))
	{
		if (keydata.key == MLX_KEY_ESCAPE || game->error == WRONG)
		{
			game->error = WRONG;
			mlx_close_window(game->mlx);
		}
		else if (keydata.key == MLX_KEY_A)
			ft_player_action(game, LEFT);
		else if (keydata.key == MLX_KEY_S)
			ft_player_action(game, DOWN);
		else if (keydata.key == MLX_KEY_W)
			ft_player_action(game, UP);
		else if (keydata.key == MLX_KEY_D)
			ft_player_action(game, RIGHT);
	}
}
