/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baddies_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:55:49 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 13:01:01 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Draws baddy in current position if next position is NOT_YET. If there is  */
/* next position, draws baddy on it, and a floor texture on last position.   */
/* Next position becomes actual position.                                    */
void	ft_draw_baddy(t_game *game, t_baddies *baddy)
{
	if (baddy->nxt_pos.x == NOT_YET)
	{
		if (!mlx_draw_texture(game->img, &(game->baddy->texture),
				baddy->pos.x * TX_SIZE, baddy->pos.y * TX_SIZE))
			ft_error(game, LD_IMG_ERR, "draw baddy");
	}
	else
	{
		if (!mlx_draw_texture(game->img, &(game->floor->texture),
				baddy->pos.x * TX_SIZE, baddy->pos.y * TX_SIZE))
			ft_error(game, LD_IMG_ERR, "draw baddy");
		if (!mlx_draw_texture(game->img, &(game->baddy->texture),
				baddy->nxt_pos.x * TX_SIZE, baddy->nxt_pos.y * TX_SIZE))
			ft_error(game, LD_IMG_ERR, "draw baddy");
		baddy->pos = baddy->nxt_pos;
	}
}

/* Checks if baddy is over player position, in which case, send a message    */
/* and set up game->error for dead__event to start.                          */
static void	ft_check_death(t_game *game, t_baddies *baddy)
{
	if (baddy->pos.x == game->player->pos.x
		&& baddy->pos.y == game->player->pos.y)
	{
		if (game->error != DEAD)
		{
			ft_printf("You are dead! GAME OVER.\n");
			game->error = DEAD;
		}
	}
}

/* Checks if given position is good: it has no wall, collectable, exit, or   */
/* another baddy on it                                                       */
static int	ft_good_place(t_game *game, int x, int y)
{
	char		c;
	t_baddies	*baddy;

	baddy = game->baddies;
	while (baddy)
	{
		if (baddy->pos.x == x && baddy->pos.y == y)
			return (WRONG);
		baddy = baddy->next;
	}
	c = game->map->grid[y][x];
	if (c == 'C' || c == '1' || c == 'E')
		return (WRONG);
	return (GOOD);
}

/* Receives player and baddy positions as arguments for the sake of shorter  */
/* names and less lines. Calculates shorter way to get to player position.   */
static void	ft_next_pos_baddy(t_game *game, t_baddies *bdy, t_pos bp, t_pos pl)
{
	if (ft_abs(pl.x - bp.x) >= ft_abs(pl.y - bp.y))
	{
		if (ft_good_place(game, bp.x + 1, bp.y) && pl.x >= bp.x)
			bdy->nxt_pos = ft_get_pos(bp.x + 1, bp.y);
		else if (ft_good_place(game, bp.x - 1, bp.y) && pl.x <= bp.x)
			bdy->nxt_pos = ft_get_pos(bp.x - 1, bp.y);
		else if (ft_good_place(game, bp.x, bp.y - 1) && pl.y <= bp.y)
			bdy->nxt_pos = ft_get_pos(bp.x, bp.y - 1);
		else if (ft_good_place(game, bp.x, bp.y + 1))
			bdy->nxt_pos = ft_get_pos(bp.x, bp.y + 1);
	}
	else if (ft_abs(pl.x - bp.x) < ft_abs(pl.y - bp.y))
	{
		if (ft_good_place(game, bp.x, bp.y + 1) && pl.y >= bp.y)
			bdy->nxt_pos = ft_get_pos(bp.x, bp.y + 1);
		else if (ft_good_place(game, bp.x, bp.y - 1) && pl.y <= bp.y)
			bdy->nxt_pos = ft_get_pos(bp.x, bp.y - 1);
		else if (ft_good_place(game, bp.x - 1, bp.y) && pl.x <= bp.x)
			bdy->nxt_pos = ft_get_pos(bp.x - 1, bp.y);
		else if (ft_good_place(game, bp.x + 1, bp.y))
			bdy->nxt_pos = ft_get_pos(bp.x + 1, bp.y);
	}
}

/* Manage action turn of each baady. Check for death situation before and    */
/* after moving. Checks for best movement and draws it                       */
void	ft_action_baddies(t_game *game)
{
	t_baddies	*baddy;

	baddy = game->baddies;
	while (baddy)
	{
		ft_check_death(game, baddy);
		ft_next_pos_baddy(game, baddy, baddy->pos, game->player->pos);
		ft_draw_baddy(game, baddy);
		ft_check_death(game, baddy);
		baddy = baddy->next;
	}
}
