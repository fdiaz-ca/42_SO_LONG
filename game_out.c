/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_out.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:35:46 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/24 19:24:18 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (game->pl_tx)
		mlx_delete_xpm42(game->pl_tx);
}

/* In case, it shows a winner message. Then it closes and frees everything.  */
void	ft_game_over(t_game *game)
{
	if (game->col_cnt == 0 && game->error == WIN)
	{
		ft_printf("\n\n\n\n\n\n\n\t\t\t\t   WELL DONE!!!\n\n");
		ft_printf("\t\t\t\t  -- YOU WIN --\n\n\t\t\t\t--< GAME OVER >--\n\n");
	}
	ft_free_textures(game);
	if (game->pl_img)
		mlx_delete_image(game->mlx, game->pl_img);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	ft_free_map(game->map);
	free(game);
}
