

#include "minishell.h"

int	find_spliter(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i])
			return (1);
		i++;
	}
	return (0);
}

int	my_token(char *s)
{
	int	token;

	token = 0;
	if (!ft_strcmp(s, "|"))
		token = 5;
	else if (!ft_strcmp(s, ">"))
		token = 2;
	else if (!ft_strcmp(s, "<"))
		token = 3;
	else if (!ft_strcmp(s, "<<"))
		token = 4;
	else if (!ft_strcmp(s, ">>"))
		token = 9;
	else if (!ft_strcmp(s, "||"))
		token = 6;
	return (token);
}

t_nor_sp	*norm_sp()
{
	t_nor_sp	*norm;

	norm = malloc(sizeof(t_nor_sp));
	norm->check = 0;
	norm->check_q = 0;
	norm->quotes = 0;
	norm->node = NULL;
	norm->st = NULL;
	norm->j = 0;
	norm->i = 0;
	norm->e = 0;
	norm->token = 0;
	norm->k = 0;
	return (norm);
}

int	count_nosplit(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && !find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
		{
			while (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
			{
				(*norm)->quotes = str[(*norm)->i];
				(*norm)->i++;
				while (str[(*norm)->i] && (str[(*norm)->i] != (*norm)->quotes))
					(*norm)->i++;
			}
		}
		else
			(*norm)->i++;
	}
	return ((*norm)->i);
}

char	*fill_quotes(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
	{
		(*norm)->node[(*norm)->j] = str[(*norm)->i];
		(*norm)->quotes = str[(*norm)->i];
		(*norm)->i++;
		(*norm)->j++;
		while (str[(*norm)->i] && (str[(*norm)->i] != (*norm)->quotes))
		{
			(*norm)->node[(*norm)->j] = str[(*norm)->i];
			(*norm)->j++;
			(*norm)->i++;
		}
		(*norm)->node[(*norm)->j] = str[(*norm)->i];
		(*norm)->j++;
		(*norm)->i++;
		(*norm)->node[(*norm)->j] = 0;
	}
	return ((*norm)->node);
}