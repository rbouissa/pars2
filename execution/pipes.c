/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 18:53:35 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:19:43 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipes_creation(int pip_count, int **fd)
{
	int	i;

	i = 0;
	if (pip_count > 0)
	{
		while (i <= pip_count)
		{
			if (pipe(fd[i]) < 0)
				fct_error("pipe");
			i++;
		}
	}
}

int	**allocate_fd(int **fd, int pip_count, t_cmd *cmd)
{
	int	i;

	i = 0;
	fd = malloc(sizeof(int *) * (pip_count + 1));
	
	while (i <= pip_count)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i++;
	}
	g_global->id = malloc(sizeof(pid_t) * (pip_count + 1));
	g_global->count_cmd = pip_count;
	pipes_creation(pip_count, fd);
	pipe_herdoc(cmd);
	return (fd);
}

void	initiate_vars_structe(t_vars **vars, t_mini *mini, t_cmd *cmd)
{
	(*vars)->i = 0;
	(*vars)->check = 0;
	(*vars)->fd = NULL;
	(*vars)->paths = cmd_paths(mini);
	(*vars)->pip_count = count_pipes(cmd);
	(*vars)->stat1 = 0;
}

void	close_pipes(int pip_count, int **fd)
{
	int	i;

	i = 0;
	while (i <= pip_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	close_pipes2(int pip_count, int **fd, char **herdoc)
{
	int	i;

	i = 0;
	while (i <= pip_count)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	if (herdoc[0] != NULL)
	{
		close(g_global->hrd[i][0]);
		close(g_global->hrd[i][1]);
	}
}
