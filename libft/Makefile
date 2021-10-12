# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mqueguin <mqueguin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/09 23:39:23 by mqueguin          #+#    #+#              #
#    Updated: 2021/09/15 16:58:46 by mqueguin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

END		=	\033[0m
BOLD	=	\033[1m
UNDER	=	\033[4m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m

SRCS		= 		ft_isalnum.c\
					ft_isalpha.c\
					ft_isascii.c\
					ft_split.c\
					ft_isdigit.c\
					ft_isprint.c\
					ft_strchr.c\
					ft_strlcpy.c\
					ft_strlen.c\
					ft_strncmp.c\
					ft_strrchr.c\
					ft_tolower.c\
					ft_toupper.c\
					ft_atoi.c\
					ft_strdup.c\
					ft_memset.c\
					ft_bzero.c\
					ft_memcpy.c\
					ft_memccpy.c\
					ft_memcmp.c\
					ft_memmove.c\
					ft_memchr.c\
					ft_strnstr.c\
					ft_calloc.c\
					ft_substr.c\
					ft_strjoin.c\
					ft_strtrim.c\
					ft_strmapi.c\
					ft_strdel.c\
					ft_putchar.c\
					ft_putchar_fd.c\
					ft_putstr_fd.c\
					ft_putendl_fd.c\
					ft_putnbr_fd.c\
					ft_itoa.c\
					ft_free.c

SRCS_BONUS	=		ft_lstnew.c\
					ft_lstadd_front.c\
					ft_lstsize.c\
					ft_lstlast.c\
					ft_lstadd_back.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					ft_lstiter.c\
					ft_lstmap.c

HEAD		=		libft.h

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

NAME		= libft.a

CC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -I.

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			@ar rc ${NAME} ${OBJS}

bonus:		${NAME} ${OBJS} ${OBJS_BONUS}
			@ar rc ${NAME} ${OBJS} ${OBJS_BONUS}

all:		${NAME}

clean:
			@${RM} ${OBJS} ${OBJS_BONUS}

fclean:		clean
			@${RM} ${NAME}

re:			fclean all

.PHONY:		all	clean	fclean re bonus
