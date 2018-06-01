#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ismus <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/24 16:01:42 by ismus             #+#    #+#              #
#    Updated: 2017/10/24 16:34:41 by ismus            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	lem-in

FUNC	=	first.c check.c trees.c commun_rooms.c unique_ways.c last_check.c	\
			mascmp.c many_way.c output_ants.c get_arg.c

OBJ		=	$(FUNC:.c=.o)

CC		=	gcc

CFLAGS	=	-Wextra -Wall -Werror

all: $(NAME)

$(NAME): create $(OBJ)
	@$(CC) $(OBJ) -I /new_lib -L ./new_lib -lft -o $(NAME)
	@echo "\x1B[0;32m"$(NAME)" ready!"

create:
	@make -C new_lib/

$(OBJ): %.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C new_lib/ clean
	@rm -f $(OBJ)

fclean: clean
	@make -C new_lib/ fclean
	@rm -f $(NAME)

re: fclean all

.NOTPARALLEL: all $(NAME) re
