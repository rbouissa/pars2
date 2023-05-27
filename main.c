#include "minishell.h"
//cat Makefile >1| <<k <<l<<l cat>>1|ls|wc|cat >>1
//<Makefile cat <main.c | wc -l;

// t_global			*my_global;

int	ther_are_pipe(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	print_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		i = 0;
		if (tmp->cmd == NULL)
			printf("cmd = NULL\n");
		while (tmp->cmd && tmp->cmd[i])
		{
			printf("%s\n", tmp->cmd[i]);
			i++;
		}
		printf("infile = %d\n", tmp->infile);
		printf("outfile = %d\n", tmp->outfile);
		i = 0;
		while (tmp->herdoc && tmp->herdoc[i])
		{
			printf("herdoc = %s\n", tmp->herdoc[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	alot_of_spliter(char *s)
{
	int	i;

	i = 0;
	while (find_spliter(s[i], "|<> \t"))
		i++;
	if (s[i] && !find_spliter(s[i], "|<> \t"))
		return (1);
	else
		return (0);
}

void	init_my_global(void)
{
	g_global->m_cmd = NULL;
	g_global->hrdsize = 0;
	g_global->status = 0;
	g_global->hrd = NULL;
	g_global->hrd_id = 0;
	g_global->count_cmd = 0;
	g_global->id = NULL;
	g_global->status = 0;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		ft_free(tmp->cmd);
		ft_free(tmp->herdoc);
		tmp = tmp->next;
	}
	free(cmd);
}

t_main	*init_main_struct()
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	main->str = NULL;
	main->str_2 = NULL;
	main->i = 0;
	main->k = 0;
	return (main);
}
t_main	*main_take(t_main *m)
{
	tcgetattr(0, &(m->term));
	m->term2 = m->term;
	m->term.c_lflag &= ~ISIG;
	m->term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &(m->term));
	m->str = readline("minishell>");
	tcsetattr(0, TCSANOW, &(m->term2));
	if (!m->str)
		(write(1, "exit\n", 5), free(m->str), exit(g_global->status));
	add_history(m->str);
	return (m);
}

t_mini	*main_initialisation(char **env, t_main **m)
{
	t_mini	*mini;

	*m = init_main_struct();
	g_global = malloc(sizeof(t_global));
	mini = env_iniit(env);
	g_global->m_env = mini;
	init_my_global();
	(signal(SIGINT, ctrlc_handler), signal(SIGQUIT, ctrld_handler));
	return (mini);
}
void	check_sl_zero(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = -1;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
			if (ft_strcmp(tmp->cmd[i], "\"\"") == 0)
			{
				free(tmp->cmd[i]);
				tmp->cmd[i] = ft_strdup("\0");
			}
		tmp = tmp->next;
	}
}
void	check_free(t_main **m, t_cmd **commands)
{
	free((*m)->str);
	(*m)->str = NULL;
	if ((*m)->str_2 != NULL)
		free((*m)->str_2);
	if ((*m)->str_2 != NULL && (*m)->k)
	{
		(*m)->k = 0;
		ft_free_cmd2(*commands);
		*commands = NULL;
		(*m)->str_2 = NULL;
	}
}
void	expand_and_take(t_mini **mini, t_main **m)
{
	*m = main_take(*m);
	(*m)->str_2 = new_expand((*m)->str, *mini);
}
int	main(int argc, char **argv, char **env)
{
	t_list	*cmd;
	t_cmd	*commands;
	t_mini	*mini;
	t_main	*m;

	(void)argc;
	(void)argv;
	mini = main_initialisation(env, &m);
	while (1)
	{
		expand_and_take(&mini, &m);
		if (m->str_2 != NULL && check_in_main(m->str_2))
		{
			m->k = 1;
			if (m->str_2[0])
			{
				send_cmd(&cmd, &commands, m->str_2);
				if (commands == NULL)
					continue ;
				if (commands->infile != -1 && commands->outfile != -1)
					exec_cmd(mini, commands, env);
			}
		}
		check_free(&m, &commands);
	}
}
int	check_in_main(char *str_2)
{
	if (str_2 != NULL && check_eroor(str_2) && alot_of_spliter(str_2))
		return (1);
	else
		return (0);
}
void	send_cmd(t_list **cmd, t_cmd **commands, char *str_2)
{
	*cmd = ft_split_them(str_2);
	*commands = split_to_commands(*cmd);
	check_sl_zero(*commands);
}
