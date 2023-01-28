# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdiaz-ca <fdiaz-ca@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 20:39:28 by fdiaz-ca          #+#    #+#              #
#    Updated: 2023/01/28 13:31:05 by fdiaz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long

NAME_BONUS = so_long_bonus

CFLAGS	= -Wextra -Wall -Werror

GLFW	= /System/Volumes/Data/sgoinfre/goinfre/Perso/fdiaz-ca/homebrew/Cellar/glfw/3.3.8/lib

MLX_DIR	= ./lib/MLX42

FT_DIR	= ./lib/libft

INC		= -I $(MLX_DIR)/include -I $(FT_DIR)

LIBS	= -lglfw -L $(GLFW) $(MLX_DIR)/libmlx42.a $(FT_DIR)/libft.a

SRCS	= so_long.c map_init.c game_init.c game_out.c moves.c \

SRCS_BONUS	=	so_long_bonus.c map_init_bonus.c game_init_bonus.c \
				game_init2_bonus.c game_out_bonus.c \
				moves_bonus.c moves2_bonus.c baddies_bonus.c \

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

OBJS	= $(SRCS:.c=.o)


GRN = \033[1;32m
RED = \033[1;31m
YEL = \033[1;33m
WHT = \033[1;37m
EOC = \033[1;0m

all:	$(NAME)

$(NAME):	$(SRCS)
	@echo "$(YEL)==== Building MLX42 ====$(EOC)"
	@make -C $(MLX_DIR) --silent
	@echo "$(GRN)  _==__==_Done_==__==_       $(EOC)"
	@echo "$(YEL)==== Building Libft ====$(EOC)"
	@make -C $(FT_DIR) --silent
	@echo "$(GRN)  _==__==_Done_==__==_       $(EOC)"
	@echo "$(YEL)==== Compiling So_Long ====$(EOC)"
	@gcc -c $(SRCS) $(CFLAGS) $(INC)
	@gcc $(OBJS) $(CFLAGS) $(LIBS) $(INC) -o $(NAME)
	@echo "$(GRN)==== So_Long Compiled ====$(EOC)"

bonus:	$(NAME_BONUS)

$(NAME_BONUS):
	@echo "$(YEL)==== Building MLX42 ====$(EOC)"
	@make -C $(MLX_DIR) --silent
	@echo "$(YEL)==== Building Libft ====$(EOC)"
	@make -C $(FT_DIR) --silent
	@echo "$(GRN)  _==__==_Done_==__==_       $(EOC)"
	@echo "$(YEL)==== Compiling So_Long_Bonus ====$(EOC)"
	@gcc -c $(SRCS_BONUS) $(CFLAGS) $(INC)
	@gcc $(OBJS_BONUS) $(CFLAGS) $(LIBS) $(INC) -o $(NAME_BONUS)
	@echo "$(GRN)==== So_Long_Bonus Compiled ====$(EOC)"

clean:
	@echo "$(YEL)==== Deleting objects files ====$(EOC)"
	@make -C $(MLX_DIR) clean --silent
	@make -C $(FT_DIR) clean --silent
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@echo "$(YEL)       ==== Done ====  $(EOC)"

fclean:	clean
	@echo "$(YEL)==== Deleting binary files ====$(EOC)"
	@make -C $(MLX_DIR) fclean --silent
	@make -C $(FT_DIR) fclean --silent
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "$(YEL)       ==== Done ====  $(EOC)"

re:		fclean all

.PHONY: all, clean, fclean, re, bonus