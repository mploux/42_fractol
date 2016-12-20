# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mploux <mploux@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/10 06:04:58 by mploux            #+#    #+#              #
#    Updated: 2016/12/20 15:13:34 by mploux           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
FILES = main.c\
		fractol.c\
		error.c\
		inputs/input.c\
		inputs/keyboard.c\
		inputs/mouse.c\
		maths/vec2.c\
		maths/vec3.c\
		maths/vec4.c\
		maths/maths.c\
		graphics/renderer.c\
		graphics/color.c\
		graphics/bitmap.c\
		graphics/line.c\
		fractols/mandelbrot.c\
		fractols/koch.c\
		fractols/julia.c

REPS = 	maths\
		inputs\
		graphics\
		fractols

BIN = bin/
DIRS = $(addprefix $(BIN),$(REPS))
SRC = $(addprefix src/,$(FILES))
OBJ = $(addprefix $(BIN),$(FILES:.c=.o))

INCLUDES = -I includes/ -I libmlx/ -I libft/
LIBS = -L libmlx/ -L libft/

CFLAGS = -lmlx -lft -lm -framework OpenGl -framework AppKit
FLAGS = -Wall -Wextra

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(BIN) $(OBJ)
	@make -C libft/
	@make -C libmlx/
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(INCLUDES) $(LIBS) $(CFLAGS)

$(BIN):
	@mkdir $(BIN)
	@mkdir -p $(DIRS)

bin/%.o: src/%.c
	$(CC) $(FLAGS) -o $@ -c $< $(INCLUDES)

clean:
	rm -rf $(BIN)

fclean: clean
	rm -rf $(NAME)

re: fclean all
