/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_out_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:35:46 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/19 13:00:26 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Delete all textures variables                                             */
static void	ft_free_textures(t_game *game)
{
	if (game->wall)
		mlx_delete_xpm42(game->wall);
	if (game->floor)
		mlx_delete_xpm42(game->floor);
	if (game->collec)
		mlx_delete_xpm42(game->collec);
	if (game->exit)
		mlx_delete_xpm42(game->exit);
	if (game->baddy)
		mlx_delete_xpm42(game->baddy);
	if (game->player->tx0)
		mlx_delete_xpm42(game->player->tx0);
	if (game->player->tx1)
		mlx_delete_xpm42(game->player->tx1);
	if (game->player->tx2)
		mlx_delete_xpm42(game->player->tx2);
	if (game->player->tx3)
		mlx_delete_xpm42(game->player->tx3);
	if (game->player->tx4)
		mlx_delete_xpm42(game->player->tx4);
	if (game->player->tx5)
		mlx_delete_xpm42(game->player->tx5);
}

/* Delete all images variables                                               */
static void	ft_free_images(t_game *game)
{
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->txt_img)
		mlx_delete_image(game->mlx, game->txt_img);
	if (game->door)
		mlx_delete_image(game->mlx, game->door);
	if (game->player->img)
		mlx_delete_image(game->mlx, game->player->img);
}

/* Delete all baddies, and rests of variables to delete and free.            */
static void	ft_free_rests(t_game *game)
{
	t_baddies	*tmp;

	while (game->baddies)
	{
		tmp = game->baddies;
		game->baddies = tmp->next;
		free(tmp);
	}
	if (game->player)
		free(game->player);
	if (game->mlx)
		mlx_terminate(game->mlx);
}

/* In case, it shows a winner message. Then it closes and frees everything.  */
void	ft_game_over(t_game *game)
{
	if (game->col_cnt == 0 && game->error == GOOD)
	{
		ft_printf("\n\n\n\n\n\n\n\t\t\t\t   WELL DONE!!!\n\n");
		ft_printf("\t\t\t\t  -- YOU WIN --\n\n\t\t\t\t--< GAME OVER >--\n\n");
	}
	ft_free_textures(game);
	ft_free_images(game);
	ft_free_rests(game);
	ft_free_map(game->map);
	free(game);
}
