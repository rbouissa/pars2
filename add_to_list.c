#include "minishell.h"

int	check_string(char *str)
{
	int	i;
	int	k;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			k = str[i];
			i++;
			while (str[i] != k && str[i])
				i++;
			if (str[i] != k)
			{
				ft_write("syntax error exepected quote");
				return (g_global->status = 258, 0);
			}
		}
		i++;
	}
	return (1);
}

void	fct_return(void)
{
	ft_write("syntax error near unexpected token `|'");
	g_global->status = 258;
}

int	norm_err1(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	return (i);
}

int	norm_err2(char *str, int i)
{
	i++;
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	return (i);
}

int check_all_return_lite(char *str,int *i)
{
    if (str[(*i) + 1] == ' ' || str[(*i) + 1] == '\t' || str[(*i)
			+ 1] == '|')
		{
			(*i) = norm_err2(str, (*i));
			if (!str[(*i)] || str[(*i)] == '|')
				return (fct_return(), 0);
		}
		else if (!str[(*i) + 1])
			return (fct_return(), 0);
        return 1;
}

int	check_all_return(char *str, int *i)
{
	if ((str[0] == ' ' || str[0] == '\t'))
	{
		(*i) = norm_err1(str, (*i));
		if ((str[*i] == '|' || str[(*i)] == '>' || str[(*i)] == '<'))
			return (fct_return(), 0);
		else if (str[(*i)])
			(*i)++;
	}
	else if (str[0] == '|')
		return (fct_return(), 0);
	else if (str[(*i)] == '|' && (!str[(*i) + 1] || (str[(*i) + 1] == '\t'
					|| str[(*i) + 1] == ' ' || str[(*i) + 1] == '|')))
	{
        if(!check_all_return_lite(str,i))
            return 0;
	}
	else if ((str[(*i)] == '>' || str[(*i)] == '<') && !str[(*i) + 1])
		return (fct_return(), 0);
	else
		(*i)++;
	return (1);
}

int	check_eroor(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!check_all_return(str, &i))
			return (0);
	}
	return (1);
}
