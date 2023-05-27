/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:19:30 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:19:31 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shell_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_global->status = 127;
	exit(g_global->status);
}

void	parent_closing(int i, int pip_count, int **fd, char **herdoc)
{
	(void)herdoc;
	if (i == 0)
		close(fd[i][1]);
	else if (i == pip_count)
	{
		close(fd[i - 1][0]);
	}
	else
	{
		close(fd[i][1]);
		close(fd[i - 1][0]);
		close(fd[i - 1][1]);
	}
}

void	check_parent(t_vars **vars)
{
	int	stat;
	int	j;

	stat = 0;
	j = 0;
	waitpid(g_global->id[(*vars)->pip_count], &stat, 0);
	close_pipes((*vars)->pip_count, (*vars)->fd);
	while (j <= (*vars)->pip_count)
	{
		waitpid(g_global->id[j], NULL, 0);
		j++;
	}
	close_pipes(g_global->hrdsize, g_global->hrd);
	if (WIFSIGNALED(stat))
		g_global->status = 128 + WTERMSIG(stat);
	else if (WIFEXITED(stat))
		g_global->status = WEXITSTATUS(stat);
	if (g_global->id)
		free(g_global->id);
}

void	parent_waiting(t_cmd **cmd, int i, int **fd, int *n)
{
	if ((*cmd)->herdoc && (*cmd)->herdoc[0] != NULL)
		(*n)++;
	parent_closing(i, g_global->count_cmd, fd, (*cmd)->herdoc);
	if ((*cmd)->infile != -2)
		close((*cmd)->infile);
	if ((*cmd)->outfile != -2)
		close((*cmd)->outfile);
	*cmd = (*cmd)->next;
}

void	parent_waiting_uniq(int **fd, int *i, t_cmd *cmd)
{
	int	status;
	int	j;

	status = 0;
	(void)fd;
	(void)cmd;
	
	waitpid(g_global->id[*i], &status, 0);
	if (cmd->outfile != -2)
		close(cmd->outfile);
	if (cmd->infile != -2)
		close(cmd->infile);
	j = 0;
	while (j <= g_global->hrdsize)
	{
		close(g_global->hrd[j][0]);
		close(g_global->hrd[j][1]);
		j++;
	}
	if (WIFSIGNALED(status))
		g_global->status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		g_global->status = WEXITSTATUS(status);
	if (g_global->id)
		free(g_global->id);
}
