# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpouget <cassepipe@ymail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/23 16:37:33 by tpouget           #+#    #+#              #
#    Updated: 2021/09/15 14:36:55 by bajaba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

NAME			=	philo

#CC	  		  	=	gcc
CC	  		  	=	clang

INCLUDE_DIRS	=  inc

INCLUDE_FLAGS	= $(patsubst %, -I./%, $(INCLUDE_DIRS))

CFLAGS			=	-Wall -Wextra -Werror -g3

ASAN			=	#-fsanitize=address 

TSAN			=	#-fsanitize=thread

ANALYSER		=	#-fanalyzer

SOURCES			=  $(wildcard src/*.c)	

LIBS			=  -pthread

OBJ/OBJECTS		=	$(patsubst src/%.c, obj/%.o, $(SOURCES))
	

#	Rules

all:			$(NAME)

$(NAME):		${OBJ/OBJECTS}
				@echo "Linking..."
				${CC} ${LIBS} ${ASAN} ${TSAN} ${LDFLAGS} ${OBJ/OBJECTS} ${LIBS} -o $@ 

obj/%.o:		src/%.c Makefile | obj
				${CC} ${CFLAGS} ${INCLUDE_FLAGS} -c $< -o $@
obj:			
				mkdir obj

clean:			
				rm -rf obj

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

print_exec_name:
				@echo $(NAME)

.PHONY:			all clean fclean re print_exec_name
