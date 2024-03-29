# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 15:35:01 by mqueguin          #+#    #+#              #
#    Updated: 2021/11/16 16:27:09 by mqueguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	        =		philo

NAME_B          =       philo_bonus

SRCS            =       ./srcs/display.c\
						./srcs/ft_atoi.c\
						./srcs/get_time.c\
						./srcs/init_mutex.c\
						./srcs/philosophers.c\
						./srcs/routine_utils.c\
						./srcs/start_philo.c\
						./srcs/utils.c

INCLUDES_DIR     =       includes/

CC              =       gcc

OBJS            =       ${SRCS:.c=.o}

RM          =       rm -rf

FLAGS       =       -Wall -Wextra -Werror -pthread -g -fsanitize=thread 

.c.o:
					@${CC} ${FLAGS} -I${INCLUDES_DIR} -c $< -o ${<:.c=.o}
					@echo "\033[32m[ OK ]\033[0m \033[36m \033[1m${<:.s=.o}\033[0m"

all:			${NAME}

${NAME}:		${OBJS}
						@${CC} ${FLAGS} -I${INCLUDES_DIR} -o ${NAME} ${OBJS}
						@echo "\nlibft.a has been created"
						@echo "philo has been created"

clean:
						@${RM} ${OBJS} ${OBJS_B}
						@echo "\n *.o files deleted\n"

fclean:		clean
						@${RM} ${NAME} ${NAME_B}
						@echo "\nPrograms The libft and philo have been deleted\n"

re:		fclean all

.PHONY:           all     clean   fclean  re
