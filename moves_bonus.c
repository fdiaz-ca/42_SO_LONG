/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:26:37 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 12:59:59 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Returns next position, depending in actual position and passed direction. */
static t_pos	ft_get_next_pos(t_pos pos, int dir)
{
	t_pos	tmp;

	tmp = pos;
	if (dir == RIGHT)
		tmp.x = pos.x + 1;
	else if (dir == LEFT)
		tmp.x = pos.x - 1;
	else if (dir == UP)
		tmp.y = pos.y - 1;
	else if (dir == DOWN)
		tmp.y = pos.y + 1;
	return (tmp);
}

/* Checks if next move is a valid one. If it is, change player position and  */
/* increases moves counter, calls to print it. Sets up player movement.      */
static void	ft_player_action(t_game *game, int dir)
{
	game->pl_nxt_mov = ft_get_next_pos(game->player->pos, dir);
	if (game->map->grid[game->pl_nxt_mov.y][game->pl_nxt_mov.x] != '1')
	{
		if (dir == UP)
			game->player->pos.y -= 1;
		if (dir == DOWN)
			game->player->pos.y += 1;
		if (dir == LEFT)
			game->player->pos.x -= 1;
		if (dir == RIGHT)
			game->player->pos.x += 1;
		game->mov_cnt += 1;
		ft_draw_moves(game, NULL);
		game->pl_cnt = TX_SIZE;
		game->dir = dir;
	}
}

/* Manage movement of door opening. Close door image when finished.          */
static void	ft_door_moves(t_game *game)
{
	if (game->door_cnt % 4 == 0)
		game->door->instances->x -= 1;
	if (game->door_cnt == 0)
	{
		mlx_delete_image(game->mlx, game->door);
		game->door = NULL;
	}
	game->door_cnt -= 1;
}

/* Opens and closes dead event. Change player texture to dead one, send a    */
/* message and start movement                                                */
static void	ft_dead_moves(t_game *game)
{
	if (game->dead_cnt < 0)
	{
		game->player->dead = mlx_load_xpm42(TX_DEAD);
		if (!game->player->dead)
			ft_error(game, LD_IMG_ERR, "dead load");
		if (!mlx_draw_texture(game->player->img,
				&(game->player->dead->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "game->player->dead");
		game->dead_cnt = TX_SIZE * 2;
		ft_draw_moves(game, "YOU ARE DEAD!!!");
	}
	game->player->img->instances->y -= 1;
	game->dead_cnt -= 1;
	if (game->dead_cnt == 0)
	{
		mlx_delete_xpm42(game->player->dead);
		game->player->dead = NULL;
		game->error = WRONG;
	}
}

/* Hook to manage game. Reads key pressed if there is no event going on      */
void	ft_capt_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->door_cnt >= 0)
		ft_door_moves(game);
	else if (game->dir != 0)
		ft_player_moves(game);
	else if (game->error == DEAD)
		ft_dead_moves(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) || game->error != GOOD)
	{
		game->error = WRONG;
		mlx_close_window(game->mlx);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ft_player_action(game, UP);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ft_player_action(game, DOWN);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		ft_player_action(game, LEFT);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		ft_player_action(game, RIGHT);
}
