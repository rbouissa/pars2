/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:19:10 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:19:12 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	struct_free(t_vars *vars)
{
	int	i;

	i = 0;
	while (i <= vars->pip_count)
	{
		free(vars->fd[i]);
		i++;
	}
	free(vars->fd);
	i = 0;
	while (vars->paths[i])
	{
		free(vars->paths[i]);
		i++;
	}
	free(vars->paths);
	free(vars);
}

void	global_free(void)
{
	int	i;

	i = 0;
	while (i <= g_global->hrdsize)
	{
		free(g_global->hrd[i]);
		i++;
	}
	free(g_global->hrd);
}

void	fct_error(char *str)
{
	perror(str);
	g_global->status = 1;
	//exit(g_global->status);
}
