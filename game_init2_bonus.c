/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:39:45 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 13:00:39 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Receives a position in map, saves it if it's a collectable or a baddy.    */
void	ft_get_cb(t_map *map, int x, int y)
{
	t_baddies	*baddy;

	if (map->grid[y][x] == 'C')
		map->n_collec += 1;
	else
	{
		baddy = (t_baddies *)malloc(sizeof(t_baddies));
		if (!baddy)
			map->error = WRONG;
		else
		{
			baddy->pos.x = x;
			baddy->pos.y = y;
			baddy->nxt_pos.x = NOT_YET;
			baddy->nxt_pos.y = NOT_YET;
			baddy->next = map->baddies;
			map->baddies = baddy;
		}
	}
}

/* Prints in window's image and terminal a counter of moves                  */
void	ft_draw_moves(t_game *game, char *str)
{
	if (!str)
	{
		ft_printf("Moves = %i\n", game->mov_cnt);
		str = ft_strjoin(" MOVES = ", ft_itoa(game->mov_cnt));
		if (!str)
			ft_error(game, MEM_ERR, NULL);
		if (game->txt_img)
			mlx_delete_image(game->mlx, game->txt_img);
		game->txt_img = mlx_put_string(game->mlx, str, 0,
				(game->map->n_lines) * TX_SIZE);
		if (!game->txt_img)
			ft_error(game, LD_IMG_ERR, "txt_img");
		free(str);
	}
	else
	{
		if (game->txt_img)
			mlx_delete_image(game->mlx, game->txt_img);
		game->txt_img = mlx_put_string(game->mlx, str, 0,
				(game->map->n_lines) * TX_SIZE);
	}
	if (!game->txt_img)
		ft_error(game, MEM_ERR, "draw_moves");
}

/* Initializes and returns a player structure                                */
static t_player	*ft_new_player(void)
{
	t_player	*tmp;

	tmp = (t_player *)malloc(sizeof(t_player));
	if (!tmp)
		return (NULL);
	tmp->img = NULL;
	tmp->tx0 = NULL;
	tmp->tx1 = NULL;
	tmp->tx2 = NULL;
	tmp->tx3 = NULL;
	tmp->tx4 = NULL;
	tmp->tx5 = NULL;
	tmp->dead = NULL;
	tmp->pos.x = NOT_YET;
	tmp->pos.y = NOT_YET;
	return (tmp);
}

/* Creates and returns a player set up                                       */
t_player	*ft_load_player(t_game *game)
{
	t_player	*player;

	player = ft_new_player();
	if (!player)
		ft_error(game, MEM_ERR, NULL);
	player->pos.x = game->map->player.x;
	player->pos.y = game->map->player.y;
	player->tx0 = mlx_load_xpm42(TX_0);
	player->tx1 = mlx_load_xpm42(TX_1);
	player->tx2 = mlx_load_xpm42(TX_2);
	player->tx3 = mlx_load_xpm42(TX_3);
	player->tx4 = mlx_load_xpm42(TX_4);
	player->tx5 = mlx_load_xpm42(TX_5);
	player->img = mlx_new_image(game->mlx, TX_SIZE, TX_SIZE);
	if (!(player->img && player->tx0 && player->tx1 && player->tx2
			&& player->tx3 && player->tx4 && player->tx5))
		ft_error(game, LD_IMG_ERR, "new player");
	if (!mlx_draw_texture(player->img, &(player->tx0->texture), 0, 0))
		ft_error(game, LD_IMG_ERR, "player tx0");
	return (player);
}
