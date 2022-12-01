/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:13:36 by fdiaz-ca          #+#    #+#             */
/*   Updated: 2022/11/28 15:18:01 by fdiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "MLX42/MLX42.h"

# define WRONG 0
# define BAD_ARG -10
# define MEM_ERR -11
# define LEC_ERR -12
# define LD_IMG_ERR -13
# define WRG_MAP -14
# define NOT_YET -15
# define DEAD -16
# define UP -17
# define DOWN -18
# define LEFT -19
# define RIGHT -20
# define TX_SIZE 32
# define TX_WALL "./imgs/wall.xpm42"
# define TX_COLL "./imgs/key.xpm42"
# define TX_EXIT "./imgs/door0.xpm42"
# define TX_EXIT1 "./imgs/door1.xpm42"
# define TX_EXIT2 "./imgs/door2.xpm42"
# define TX_FLOOR "./imgs/floor.xpm42"
# define TX_PLAYER "./imgs/player.xpm42"
# define TX_BADDY "./imgs/baddy.xpm42"
# define TX_0 "./imgs/bob0.xpm42"
# define TX_1 "./imgs/bob1.xpm42"
# define TX_2 "./imgs/bob2.xpm42"
# define TX_3 "./imgs/bob3.xpm42"
# define TX_4 "./imgs/bob4.xpm42"
# define TX_5 "./imgs/bob5.xpm42"
# define TX_DEAD "./imgs/dead.xpm42"

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_player
{
	xpm_t		*tx0;
	xpm_t		*tx1;
	xpm_t		*tx2;
	xpm_t		*tx3;
	xpm_t		*tx4;
	xpm_t		*tx5;
	xpm_t		*dead;
	mlx_image_t	*img;
	t_pos		pos;
}				t_player;

typedef struct s_baddies
{
	t_pos				pos;
	t_pos				nxt_pos;
	struct s_baddies	*next;
}				t_baddies;

typedef struct s_map
{
	char		**grid;
	int			n_colum;
	int			n_lines;
	int			n_collec;
	t_baddies	*baddies;
	t_pos		player;
	t_pos		door;
	int			error;
}				t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*txt_img;
	mlx_image_t	*door;
	t_map		*map;
	xpm_t		*wall;
	xpm_t		*floor;
	xpm_t		*collec;
	xpm_t		*exit;
	xpm_t		*baddy;
	int			mov_cnt;
	int			col_cnt;
	t_player	*player;
	t_baddies	*baddies;
	int			dir;
	int			door_cnt;
	int			dead_cnt;
	int			pl_cnt;
	t_pos		pl_nxt_mov;
	int			error;
}				t_game;

t_map		*ft_init_map(int argc, char **argv, t_map *map, int fd);
void		ft_free_map(t_map *map);
t_pos		ft_get_pos(int x, int y);
void		ft_game_on(t_game *game, t_map *map);
void		ft_game_over(t_game *game);
void		ft_capt_hook(void *param);
t_player	*ft_load_player(t_game *game);
void		ft_draw_moves(t_game *game, char *str);
void		ft_error(t_game *game, int error, char *str);
void		ft_player_moves(t_game *game);
void		ft_get_cb(t_map *map, int x, int y);
void		ft_draw_baddy(t_game *game, t_baddies *baddy);
void		ft_action_baddies(t_game *game);
void		ft_ver_baddies(t_game *game, t_baddies *baddy);

#endif