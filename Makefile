NAME = parsing


FLAGS = -Wall -Werror -Wextra -g -fsanitize=address
RM = rm -f

SRC = main.c libft_helpers.c test_split.c list_utils.c add_to_list.c creat_list_command.c ft_split.c 
OBJ = $(SRC:.c=.o)


all:	$(NAME) 

$(NAME):	$(OBJ) $(OBJ_S)
	cc  $(FLAGS) -lreadline $(OBJ) -o $(NAME)


clean:	
	$(RM) $(OBJ) 

fclean:	clean
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re bonus