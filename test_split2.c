

#include "minishell.h"

char	*fill_node(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && !find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (str[(*norm)->i] == 34 || str[(*norm)->i] == 39)
			(*norm)->node = fill_quotes(norm, str);
		else
		{
			{
				(*norm)->node[(*norm)->j] = str[(*norm)->i];
				(*norm)->j++;
				(*norm)->i++;
			}
			(*norm)->node[(*norm)->j] = 0;
		}
	}
	return ((*norm)->node);
}

int	count_spl(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (find_spliter(str[(*norm)->i], "|<>"))
			(*norm)->j++;
		(*norm)->i++;
	}
	return ((*norm)->j);
}

char	*fill_sp(t_nor_sp **norm, char *str)
{
	while (str[(*norm)->i] && find_spliter(str[(*norm)->i], "|<> \t"))
	{
		if (find_spliter(str[(*norm)->i], "|<>"))
		{
			(*norm)->st[(*norm)->j] = str[(*norm)->i];
			(*norm)->j++;
			(*norm)->i++;
			if (str[(*norm)->i] == str[(*norm)->i - 1])
			{
				(*norm)->st[(*norm)->j] = str[(*norm)->i];
				(*norm)->i++;
				(*norm)->j++;
			}
			break ;
		}
		(*norm)->i++;
	}
	(*norm)->st[(*norm)->j] = 0;
	return ((*norm)->st);
}

void	fill_struct(t_nor_sp **norm, t_list **s, char *str)
{
	(*norm)->node = malloc((*norm)->i - (*norm)->k + 1);
	(*norm)->i = (*norm)->k;
	(*norm)->j = 0;
	(*norm)->node = fill_node(norm, str);
	ft_lstadd_back(s, ft_lstnew(string_no_quotes((*norm)->node), 0));
}

void	fill_struct2(t_nor_sp **norm, t_list **s, char *str)
{
	(*norm)->st = malloc((*norm)->j + 1);
	(*norm)->j = 0;
	(*norm)->i = (*norm)->k;
	(*norm)->st = fill_sp(norm, str);
	(*norm)->token = my_token((*norm)->st);
	ft_lstadd_back(s, ft_lstnew(string_no_quotes((*norm)->st), (*norm)->token));
}