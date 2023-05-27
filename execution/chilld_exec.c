/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chilld_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:18:41 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:18:45 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**cmd_paths(t_mini *mini)
{
	t_mini	*tmp;
	char	*paths;
	char	**spl_path;
	int		i;

	i = 0;
	paths = NULL;
	tmp = mini;
	while (tmp)
	{
		if (ft_strcmp(tmp->data_var, "PATH") == 0)
		{
			paths = tmp->data_val;
			break ;
		}
		else
			tmp = tmp->next;
	}
	spl_path = ft_split(paths, ':');
	while (spl_path[i])
	{
		spl_path[i] = ft_strjoin(spl_path[i], "/");
		i++;
	}
	return (spl_path);
}

void	mini_execution(char **cmd, char **env)
{
	if (cmd[0][1] == '\0')
	{
		if (cmd[0][0] == '/')
		{
			printf("minishell: %s: is a directory\n", cmd[0]);
			exit(g_global->status = 126);
		}
		else
		{
			printf("minishell:%s: filename argument required\n%s", cmd[0],
					cmd[0]);
			printf(": usage:%s filename [arguments]\n", cmd[0]);
			exit(g_global->status = 2);
		}
	}
	else if (execve(cmd[0], cmd, env) == -1)
	{
		printf("minishell: %s: is a directory\n", cmd[0]);
		exit(g_global->status = 126);
	}
}

void	child_execution(t_cmd *cmd, char **paths, char **env, int *n)
{
	if (cmd->infile != -2 && cmd->infile != -1)
		if (dup2(cmd->infile, STDOUT_FILENO) == -1)
			fct_error("dup2");
	if (cmd->outfile != -2 && cmd->outfile != -1)
		if (dup2(cmd->outfile, STDIN_FILENO) == -1)
			fct_error("dup2");
	if (cmd->herdoc && cmd->herdoc[0] != NULL)
	{
		if (dup2(g_global->hrd[*n][0], STDIN_FILENO) == -1)
			fct_error("dup2");
		close(g_global->hrd[*n][0]);
		close(g_global->hrd[*n][1]);
	}
	if (execute_builts(g_global->m_env, (cmd)->cmd) == 1)
		exit(g_global->status = 0);
	if (cmd->cmd && cmd->cmd[0] && (cmd->cmd[0][0] == '/'
			|| cmd->cmd[0][0] == '.') && access(cmd->cmd[0], F_OK) == 0)
		mini_execution(cmd->cmd, env);
	else if (cmd->cmd[0])
		execute(cmd->cmd, paths, env);
	else
		exit(g_global->status);
}

void	sort_in_pipe(int pip_count, int **fd, int i)
{
	if (i == 0)
	{
		close(fd[i][0]);
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
		close_pipes(pip_count, fd);
	}
	else if (i == pip_count)
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
		close_pipes(pip_count, fd);
	}
	else
	{
		close(fd[i - 1][1]);
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);
		close(fd[i][0]);
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
		close_pipes(pip_count, fd);
	}
}

void	execute(char **cmd, char **paths, char **env)
{
	int	j;

	j = 0;
	while (paths[j])
	{
		paths[j] = ft_strjoin(paths[j], cmd[0]);
		if (access(paths[j], F_OK) == 0)
		{
			if (execve(paths[j], cmd, env) == -1)
				fct_error("execve");
		}
		else
		{
			j++;
			free(paths[j - 1]);
		}
	}
	if (paths[j] == NULL)
		shell_error(cmd[0]);
}
