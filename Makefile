# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/16 16:42:45 by dbolilyi          #+#    #+#              #
#    Updated: 2018/09/23 13:17:55 by dbolilyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC =	3d/main3d.c \
		3d/CLrender.c \
		3d/SRC/minimap.c \
		3d/SRC/input_validation.c \
		3d/SRC/inside_sector.c \
		3d/SRC/set_get_pixels.c \
		3d/SRC/add_delete_picture.c \
		3d/SRC/draw_hud.c \
		3d/SRC/get_by_pointer.c \
		3d/SRC/sector_animations.c \
		3d/SRC/wall_animations.c \
		3d/SRC/hud_game.c \
		3d/SRC/backpack.c \
		3d/SRC/checkpoints.c \
		3d/SRC/using_cards.c \
		3d/SRC/button_f_up.c \
		3d/SRC/key_up_hook.c \
		3d/SRC/key_down_hook.c \
		3d/SRC/mouse_move_right_wheel.c \
		3d/SRC/mouse_left_up.c \
		3d/SRC/player_moving.c \
		main.c \
		save_list.c \
		display.c \
		draw_pixels.c \
		draw_line.c \
		map_redactor.c \
		save_new_list.c \
		write_list.c \
		find_walls.c \
		sector_in_sector.c \
		delete.c \
		sort_sector.c \
		sprite.c \
		delete_memory.c \
		portal.c \
		player.c \
		sector.c \
		check_option.c \
		walls.c \
		save.c \
		load.c \
		3d/SRC2/check_collisions.c \
		3d/SRC2/do_animations.c \
		3d/SRC2/enemies_main_functions.c \
		3d/SRC2/enemy_intelligence0.c \
		3d/SRC2/enemy_intelligence1.c \
		3d/SRC2/enemy_intelligence2.c \
		3d/SRC2/guns_mechanic.c \
		3d/SRC2/loop.c \
		3d/SRC2/main_loops.c \
		3d/SRC2/read_from_files.c	

OBJ = $(SRC:.c=.o)

INC =	-I./frameworks/SDL2.framework/Headers\
		-I./frameworks/SDL2_ttf.framework/Headers\
		-I./frameworks/SDL2_mixer.framework/Versions/A/Headers

ERRFL = -Wall -Wextra -g # -Werror

FL = -F./frameworks \
	-rpath ./frameworks \
	-framework SDL2 -framework SDL2_ttf -framework SDL2_mixer -framework OpenCL

all: $(NAME)

$(OBJ): %.o: %.c
	@echo "\033[93mCompiling \033[0m$@"
	@cc $(ERRFL) -c -o $@ $< $(INC)

$(NAME): $(OBJ)
	@echo "\033[93mCompiling libft\033[0m"
	@make -C ./libft
	@echo "\033[93mCompiling $(NAME)\033[0m"
	@gcc $(ERRFL) $(FL) -o $@ $(OBJ) -L libft/ ./libft/libft.a 
	@echo "\033[92mDONE\033[0m"
	

clean:
	@echo "\033[91mDeleting libft objects\033[0m"
	@make -C libft/ clean
	@echo "\033[91mDeleting $(NAME) objects\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[91mDeleting libft.a\033[0m"
	@make -C libft/ fclean
	@echo "\033[91mDeleting $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean \
	all

.PHONY: all clean fclean re

.NOTPARALLEL: all clean fclean re
