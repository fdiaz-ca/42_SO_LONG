/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:49:54 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 12:59:47 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Sets up door opening event. Sends a message. Changes texture to open one, */
/* creates image for bars, and prepares it to be move.                       */
static void	ft_door_event(t_game *game)
{
	xpm_t		*tmp_tx;

	ft_draw_moves(game, "DOOR OPENS!!!");
	game->door = mlx_new_image(game->mlx, TX_SIZE, TX_SIZE);
	tmp_tx = mlx_load_xpm42(TX_EXIT1);
	if (!game->door || !tmp_tx)
		ft_error(game, MEM_ERR, "game->door");
	if (!mlx_draw_texture(game->img, &(tmp_tx->texture),
			game->map->door.x * TX_SIZE, game->map->door.y * TX_SIZE))
		ft_error(game, MEM_ERR, "doortx1 to img");
	mlx_delete_xpm42(tmp_tx);
	tmp_tx = mlx_load_xpm42(TX_EXIT2);
	if (!tmp_tx)
		ft_error(game, MEM_ERR, "doortx2");
	if (!mlx_draw_texture(game->door, &(tmp_tx->texture), 0, 0))
		ft_error(game, MEM_ERR, "doortx2 to img");
	mlx_delete_xpm42(tmp_tx);
	if (mlx_image_to_window(game->mlx, game->door,
			game->map->door.x * TX_SIZE, game->map->door.y * TX_SIZE) < 0)
		ft_error(game, LD_IMG_ERR, "game->door to win");
	game->door_cnt = TX_SIZE * 2;
}

/* Manage player's movement on y axis. Changes textures to create animation. */
static void	ft_mov_vert(t_game *game, int dir)
{
	int32_t	pos;

	pos = (game->player->img->instances->y % TX_SIZE) / 4;
	if (pos == 1 || pos == 6)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx0->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov vert");
	if (pos == 2 || pos == 5)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx5->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov vert");
	if (dir == UP)
		game->player->img->instances->y -= 1;
	if (dir == DOWN)
		game->player->img->instances->y += 1;
}

/* Manage player's movement on x axis. Changes textures to create animation. */
static void	ft_mov_horiz(t_game *game, int dir)
{
	int32_t	pos;

	pos = (game->player->img->instances->x % TX_SIZE) / 4;
	if (pos == 1 || pos == 6)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx2->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov horiz");
	if (pos == 2 || pos == 5)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx3->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov horiz");
	if (pos == 3 || pos == 4)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx4->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov horiz");
	if (pos == 0 || pos == 7)
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx1->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "mov horiz");
	if (dir == LEFT)
		game->player->img->instances->x -= 1;
	if (dir == RIGHT)
		game->player->img->instances->x += 1;
}

/* Delete collectable element from map, loads a floor texture instead,       */
/* decreases collected_counter, if it reaches zero, calls to open the door.  */
static void	ft_player_collects(t_game *game)
{
	game->col_cnt -= 1;
	game->map->grid[game->player->pos.y][game->player->pos.x] = '0';
	if (!mlx_draw_texture(game->img, &(game->floor->texture),
			game->player->pos.x * TX_SIZE, game->player->pos.y * TX_SIZE))
		ft_error(game, LD_IMG_ERR, "floor->texture collec");
	if (game->col_cnt == 0)
		ft_door_event(game);
}

/* Manages player movement. When finish, checks if position has a collectable*/
/* If it's exit position and it's open, closes hook window. If not,          */
/* Loads player repose texture. Calls baddies turn to act.                   */
void	ft_player_moves(t_game *game)
{
	if (game->dir == RIGHT)
		ft_mov_horiz(game, RIGHT);
	else if (game->dir == LEFT)
		ft_mov_horiz(game, LEFT);
	else if (game->dir == UP)
		ft_mov_vert(game, UP);
	else if (game->dir == DOWN)
		ft_mov_vert(game, DOWN);
	game->pl_cnt -= 1;
	if (game->pl_cnt == 0)
	{
		game->dir = 0;
		if (game->map->grid[game->player->pos.y][game->player->pos.x] == 'C')
			ft_player_collects(game);
		if ((game->map->grid[game->player->pos.y][game->player->pos.x] == 'E')
				&& (game->col_cnt == 0))
			mlx_close_window(game->mlx);
		if (!mlx_draw_texture(game->player->img,
				&(game->player->tx0->texture), 0, 0))
			ft_error(game, LD_IMG_ERR, "player tx0");
		ft_action_baddies(game);
	}
}
