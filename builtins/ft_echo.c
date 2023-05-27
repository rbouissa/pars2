/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: met-tahe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:53:00 by met-tahe          #+#    #+#             */
/*   Updated: 2023/03/08 11:53:02 by met-tahe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_n(char *cmd, int *n, int *nb_arg)
{
	size_t	i;

	i = 2;
	if (cmd)
	{
		if (ft_strncmp(cmd, "-n", 2) == 0)
		{
			while (cmd[i] == 'n' && cmd[i] != '\0')
				i++;
			if (ft_strlen(cmd) == i)
			{
				*n = 1;
				*nb_arg = 2;
			}
		}
	}
}

t_echo	*init_echo(char *cmd)
{
	t_echo	*echo;

	echo = malloc(sizeof(t_echo));
	echo->n = 0;
	echo->nb_arg = 1;
	echo->j = 0;
	echo->i = 2;
	check_n(cmd, &(echo->n), &(echo->nb_arg));
	return (echo);
}

int	len_case(char **cmd, int i, int nb_arg)
{
	while (cmd[nb_arg][i] == 'n' && cmd[nb_arg][i] != '\0')
		i++;
	return (i);
}

void	check_option(int n)
{
	if (n == 0)
		printf("\n");
}

void	echo(char **cmd)
{
	t_echo	*echo;

	echo = init_echo(cmd[1]);
	while (cmd[echo->nb_arg])
	{
		if (ft_strncmp(cmd[echo->nb_arg], "-n", 2) == 0 && echo->n == 1)
		{
			echo->i = len_case(cmd, echo->i, echo->nb_arg);
			if (ft_strlen(cmd[echo->nb_arg]) == echo->i && echo->j == 0)
			{
				(echo->nb_arg++);
				continue ;
			}
			echo->j = 1;
			(printf("%s", cmd[echo->nb_arg]), printf(" "));
		}
		else
		{
			echo->j = 1;
			printf("%s", cmd[echo->nb_arg]);
		}
		if (cmd[++(echo->nb_arg)])
			printf(" ");
	}
	check_option(echo->n);
}
