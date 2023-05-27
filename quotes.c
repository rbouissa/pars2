

#include "minishell.h"

int	size_of_quotes(char *c)
{
    int i;
    int j;
    
    i= 0 ;
    j = 0;
    while (c[i] != '\0')
    {
        if (c[i] == '\"')
        {
            i++;
            while (c[i] && c[i] != '\"')
                {
                    i++;
                    j++;
                }
            if (c[i])
                i++;
            continue ;
        }
        if (c[i] == '\'')
        {
            i++;
            while (c[i] && c[i] != '\'')
                {
                    i++;
                    j++;
                }
            if (c[i])
                i++;
            continue ;
        }
        i++;
        j++;
    }
    return (j);
}

void	full_str_single_quotes(char *str, char *string, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != 39)
	{
		string[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}

void	full_str_double_quotes(char *str, char *string, int *i, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != 34)
	{
		string[*j] = str[*i];
		(*i)++;
		(*j)++;
	}
}
char	*string_no_quotes(char *str)
{
	char	*string;
	int		i;
	int		j;
	int		t;

	i = 0;
	j = 0;
	t = size_of_quotes(str);
	string = malloc(t + 1);
	while (str[i])
	{
		if (str[i] == 39)
		{
            
            full_str_single_quotes(str,string,&i,&j);
			if (str[i])
			{
				i++;
				continue ;
			}
		}
		if (str[i] == 34)
		{
           
            full_str_double_quotes(str,string,&i,&j);
			if (str[i])
			{
				i++;
				continue ;
			}
		}
		string[j] = str[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}
