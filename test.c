void	check_sl_zero(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = cmd;
	i = -1;
	while (tmp)
	{
		while (tmp->cmd[++i])
			if (ft_strcmp(tmp->cmd[i], "\"\"") == 0)
			{
				free(tmp->cmd[i]);
				tmp->cmd[i] = ft_strdup("\0");
			}
		tmp = tmp->next;
	}
}

void	check_free(t_main **m, t_cmd **commands)
{
	free((*m)->str);
	(*m)->str = NULL;
	if ((*m)->str_2 != NULL)
		free(m->str_2);
	if (m->str_2 != NULL && m->k)
	{
		m->k = 0;
		ft_free_cmd2(commands);
		commands = NULL;
		m->str_2 = NULL;
	}
}
int	norm_err1(char *str, int i)
{
	while ((str[i] == ' ' || str[i] == '\t') && str[i])
		i++;
	return (i);
}

int	norm_err2(char *str, int *i)
{
	i++;
	while (str[*i] && (str[*i] == '\t' || str[*i] == ' '))
		(*i)++;
	if (!str[*i] || str[*i] == '|')
		return (1);
	return (0);
}
\






void	i_for_quotes(char *c, int *i, int *j)
{
	(*i)++;
	while (c[*i] && c[*i] != '\"')
	{
		(*i)++;
		(*j)++;
	}
	if (c[*i])
		(*i)++;
}

int	size_of_quotes(char *c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\"')
		{
			i_for_quotes(c, &i, &j);
			continue ;
		}
		if (c[i] == '\'')
		{
			i_for_quotes(c, &i, &j);
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
            
            //full_str_single_quotes(str,string,&i,&j);
			i++;
			while (str[i] && str[i] != 39)
			{
				string[j] = str[i];
				i++;
				j++;
			}
			if (str[i])
			{
				i++;
				continue ;
			}
		}
		if (str[i] == 34)
		{
           
            //full_str_double_quotes(str,string,&i,&j);
			i++;
			while (str[i] && str[i] != 34)
			{
				string[j] = str[i];
				i++;
				j++;
			}
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