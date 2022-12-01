/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:25:45 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/28 14:27:18 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "MLX42/MLX42.h"

# define WRONG 0
# define BAD_ARG -10
# define MEM_ERR -11
# define LEC_ERR -12
# define WRG_MAP -13
# define NOT_YET -14
# define WIN -15
# define UP -17
# define DOWN -18
# define LEFT -19
# define RIGHT -20

# define TX_SIZE 32
# define TX_WALL "./imgs/wall.xpm42"
# define TX_COLL "./imgs/key.xpm42"
# define TX_EXIT "./imgs/door.xpm42"
# define TX_FLOOR "./imgs/floor.xpm42"
# define TX_PLAYER "./imgs/player.xpm42"

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_map
{
	char	**grid;
	int		n_colum;
	int		n_lines;
	int		n_collec;
	t_pos	player;
	int		exit;
	int		error;
}				t_map;

typedef struct s_game {
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	xpm_t			*wall;
	xpm_t			*floor;
	xpm_t			*collec;
	xpm_t			*exit;
	xpm_t			*pl_tx;
	int				mov_cnt;
	int				col_cnt;
	mlx_image_t		*pl_img;
	t_pos			player;
	t_pos			pl_nxt_mov;
	int				error;
}				t_game;

t_map	*ft_init_map(int argc, char **argv);
void	ft_free_map(t_map *map);
void	ft_player_pos(t_map *map, int x, int y);
void	ft_game_on(t_game *game, t_map *map);
void	ft_game_over(t_game *game);
void	pl_hook(mlx_key_data_t keydata, void *param);

#endif