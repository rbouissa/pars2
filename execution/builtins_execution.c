/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:18:15 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:18:23 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_builtins1(char **cmd, t_mini *mini)
{
	int	e;

	e = 0;
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			ft_export(cmd[1]);
		else
		{
			while (cmd[++e])
				ft_export(cmd[e]);
		}
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		if (cmd[1] == NULL)
			ft_unset(cmd[1], &mini);
		while (cmd[++e])
			ft_unset(cmd[e], &mini);
	}
}

int	builts_without_pipe(t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	while (cmd->cmd[0] && cmd->cmd[0][i] != '\0')
	{
		cmd->cmd[0][i] = ft_tolower(cmd->cmd[0][i]);
		i++;
	}
	if (cmd->cmd[0] == NULL)
		return (0);
	else if ((ft_strcmp(cmd->cmd[0], "export") == 0 && cmd->next == NULL
			&& cmd->cmd[1] != NULL) || (ft_strcmp(cmd->cmd[0], "unset") == 0
			&& cmd->next == NULL))
		return (mini_builtins1(cmd->cmd, mini), 1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0 && cmd->next == NULL)
		return (ft_env(mini), 1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0 && cmd->next == NULL)
		return (ft_cd(cmd->cmd[1], mini), 1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0 && cmd->next == NULL)
		return (ft_exit(cmd->cmd), 1);
	return (0);
}

int	execute_builts(t_mini *mini, char **cmd)
{
	int	i;

	i = -1;
	while (cmd[0] && cmd[0][++i] != '\0')
		cmd[0][i] = ft_tolower(cmd[0][i]);
	if (cmd[0] == NULL)
		return (0);
	else if (ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0],
			"unset") == 0)
		return (mini_builtins1(cmd, mini), 1);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(mini), 1);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (echo(cmd), g_global->status = 0, 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd[1], mini), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		return (ft_exit(cmd), 1);
	}
	return (0);
}
