

#ifndef parsing_h
# define parsing_h

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <unistd.h>
# define no_quotes 0
# define isingle_quotes 1
# define idouble_quotes 2
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_mini
{
	int				valid;
	char			*data_var;
	char			*data_val;
	struct s_mini	*next;
}					t_mini;

typedef struct s_list
{
	char			*data;
	int				token;
	struct s_list	*next;
}					t_list;

typedef struct s_file
{
	int				infile;
	int				outfile;
	char			*file;
	struct s_file	*next;
}					t_file;

typedef struct s_cmd
{
	char			**herdoc;
	char			**cmd;
	int				herdoc_token;
	int				infile;
	int				outfile;
	int				double_file;
	struct s_cmd	*next;
}					t_cmd;

char				**ft_split(char *s, char c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strjoin(char *left_str, char *buff);
t_list				*split_fuul_cmd(char **s);
char				*ft_strcpy(char *dest, char *src);
char				*ft_strdup(char *src);
char				**split_command(char *str);
void				ft_lstadd_back(t_list **lst, t_list *new);
t_list				*ft_lstnew(char *content, int t);
int					check_eroor(char *str);
void				ft_write(char *s);
int					check_string(char *str);
size_t				ft_strlen(char *s);
t_list				*ft_split_them(char *str);
t_cmd				*ft_lstnew_new(char **content, int t, int k, int p,
						char **her, int t_her);
void				ft_lstadd_back_new(t_cmd **lst, t_cmd *new);
t_cmd				*split_to_commands(t_list *comm, char *str);
int					ther_are_pipe(char *str);
t_file				*ft_last_file(void *tmp);
void				ft_lstadd_back_file(t_file **lst, t_file *new);
t_file				*ft_lstnew_file(char *content, int in, int out);
t_file				*full_file(t_list *cmd);
#endif