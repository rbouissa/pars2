/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 18:15:40 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:19:22 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc(char **herdoc)
{
	char	*s;
	int		i;
	char	*reading;

	i = -1;
	reading = NULL;
	while (herdoc && herdoc[++i])
	{
		s = readline("> ");
		if (reading != NULL)
			(free(reading), reading = NULL);
		while (s)
		{
			if (ft_strcmp(s, herdoc[i]) == 0)
			{
				free(s);
				break ;
			}
			s = new_expand(s, g_global->m_env);
			reading = ft_strjoin(reading, s);
			reading = ft_strjoin(reading, "\n");
			(free(s), s = readline("> "));
		}
	}
	return (reading);
}

void	heredoc_child(int *stat1, t_cmd *tmp1, char *line, int *j)
{
	int	k;

	k = 0;
	if (g_global->hrd_id < 0)
		fct_error("fork");
	else if (g_global->hrd_id == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, ctrld_handler));
		k = 1;
		line = heredoc(tmp1->herdoc);
		ft_putstr_fd(line, g_global->hrd[*j][1]);
		(close(g_global->hrd[*j][1]), close(g_global->hrd[*j][0]));
		(free(line), exit(0));
	}
	else
	{
		(waitpid(g_global->hrd_id, stat1, 0), close(g_global->hrd[*j][1]));
		if (WIFSIGNALED(*stat1))
		{
			g_global->status = 1;
			(*stat1) = 1;
		}
	}
	if (k == 1)
		(close(g_global->hrd[*j][1]), close(g_global->hrd[*j][0]));
}

void	read_heredoc(t_cmd *cmd, int *stat1)
{
	char	*line;
	int		j;
	t_cmd	*tmp1;

	j = 0;
	tmp1 = cmd;
	line = NULL;
	while (tmp1)
	{
		if (tmp1->herdoc && tmp1->herdoc[0] != NULL)
		{
			g_global->hrd_id = fork();
			heredoc_child(stat1, tmp1, line, &j);
			j++;
		}
		if (*stat1 == 1)
		{
			g_global->status = 1;
			break ;
		}
		tmp1 = tmp1->next;
	}
}

int	hrdpipe_num(t_cmd *tmp)
{
	t_cmd	*tmp1;
	int		i;

	tmp1 = tmp;
	i = 0;
	while (tmp1)
	{
		if (tmp1->herdoc && tmp1->herdoc[0] != NULL)
		{
			i++;
		}
		tmp1 = tmp1->next;
	}
	return (i);
}

void	pipe_herdoc(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	g_global->hrdsize = hrdpipe_num(tmp);
	g_global->hrd = malloc(sizeof(int *) * (g_global->hrdsize + 1));
	while (i <= g_global->hrdsize)
	{
		g_global->hrd[i] = malloc(sizeof(int) * 2);
		if (pipe(g_global->hrd[i]) < 0)
			fct_error("pipe");
		i++;
	}
	if (g_global->hrdsize == 0)
	{
		close(g_global->hrd[0][0]);
		close(g_global->hrd[0][1]);
	}
}
