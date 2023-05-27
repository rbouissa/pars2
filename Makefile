CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g
LIBC	= ar -rc
RM		= rm -f
NAME	= minishell
SRC		= main.c \
			ft_split.c \
			libft_helpers.c \
			builtins/ft_cd.c \
			builtins/ft_echo.c \
			builtins/ft_env.c \
			builtins/ft_pwd.c \
			builtins/ft_unset.c \
			list_utils.c \
			builtins/ft_export.c \
			builtins/ft_error.c \
			builtins/ft_exit.c \
			execution/pipes.c \
			execution/heredoc.c \
			add_to_list.c \
			test_split.c \
			creat_list_command.c \
			execution/signals.c \
			execution/free_fct.c \
			execution/builtins_execution.c \
			execution/chilld_exec.c \
			execution/parent_exec.c \
			execution/exec_cmd.c \
			freed.c \
			quotes.c\
			new_env.c\
			creat_list_command1.c\
			creat_list_command2.c\
			creat_commad_list3.c\
			creat_command_list4.c\
			test_split1.c\
			test_split2.c\
			new_env1.c\
			new_env2.c\

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)  -lreadline -L /Users/rbouissa/goinfre/homebrew/opt/readline/lib -I /Users/rbouissa/goinfre/homebrew/opt/readline/include 

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME) 

re:	fclean all

b: all clean
