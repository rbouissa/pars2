/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:19:58 by met-tahe          #+#    #+#             */
/*   Updated: 2023/05/19 21:20:01 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrlc_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	if (g_global->hrd_id)
	{
		kill(g_global->hrd_id, SIGINT);
	}
	if (g_global->id)
	{
		while (g_global->id[i])
		{
			kill(g_global->id[i], SIGINT);
			i++;
		}
	}
	g_global->status = 1;
}

void	ctrld_handler(int sig)
{
	int	i;

	(void)sig;
	i = 0;
	if (g_global->hrd_id != 0)
		rl_on_new_line();
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	if (g_global->id)
	{
		while (g_global->id[i])
		{
			kill(g_global->id[i], SIGQUIT);
			i++;
		}
	}
}
