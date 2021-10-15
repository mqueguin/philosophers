# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 15:35:01 by mqueguin          #+#    #+#              #
#    Updated: 2021/10/15 18:44:30 by mqueguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	        =		philo

NAME_B          =       philo_bonus

SRCS            =       $(wildcard srcs/*.c)

SRCS_B      =       $(wildcard Bonus/srcs_bonus/*.c)

INCLUDES_DIR     =       includes/

INCLUDES_DIR_B  =       Bonus/includes_bonus/

LIB_DIR         =       libft/

LIBFT           =       libft/libft.a

CC              =       gcc

OBJS            =       ${SRCS:.c=.o}

OBJS_B          =       ${SRCS_B:.c=.o}

RM          =       rm -rf

FLAGS       =       #-Wall -Wextra -Werror -g

.c.o:
					@${CC} ${FLAGS} -I${INCLUDES_DIR} -c $< -o ${<:.c=.o}
					@echo "\033[32m[ OK ]\033[0m ${<:.s=.o}"

all:			${NAME}

${NAME}:		${OBJS}
						@make -C ${LIB_DIR} 2>/dev/null
						@make -C ${LIB_DIR} bonus 2>/dev/null
						@${CC} ${FLAGS} -I${INCLUDES_DIR} -o ${NAME} ${OBJS} ${LIBFT}
						@echo "\nlibft.a has been created"
						@echo "philo has been created"

bonus:		${OBJS_B}
						@make -C ${LIB_DIR} 2>/dev/null
						@make -C ${LIB_DIR} bonus 2>/dev/null
						@${CC} ${FLAGS} -I ${INCLUDES_DIR_B} -o ${NAME_B} ${OBJS_B} ${LIBFT}
						@echo "\nlibft.a has been created"
						@echo "philo_bonus has been created"

clean:
						@make -C ${LIB_DIR} clean
						@${RM} ${OBJS} ${OBJS_B}
						@echo "\n *.o files deleted\n"

fclean:		clean
						@make -C ${LIB_DIR} fclean
						@${RM} ${NAME} ${NAME_B}
						@echo "\nPrograms The libft and philo have been deleted\n"

re:		fclean all

.PHONY:           all     clean   fclean  re
