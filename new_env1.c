




#include"minishell.h"

int	is_allpha1(char s)
{
	if ((s >= 65 && s <= 90) || (s >= 97 && s <= 122))
		return (1);
	return (0);
}

int	is_digit1(char s)
{
	if ((s >= 48 && s <= 57))
		return (1);
	return (0);
}

int	find_spliter1(char s, char *sp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (sp[i])
	{
		if (s == sp[i] || (!is_digit1(s) && !is_allpha1(s)))
			return (1);
		i++;
	}
	return (0);
}

char	*finnd_valeur(t_mini *env, char *str)
{
	t_mini	*tmp_env;
	char	*s;

	s = NULL;
	tmp_env = env;
	if (str[0] == '?')
	{
		s = ft_itoa(g_global->status);
		return (s);
	}
	else
	{
		while (tmp_env)
		{
			if (!ft_strcmp(tmp_env->data_var, str))
				return (tmp_env->data_val);
			tmp_env = tmp_env->next;
		}
	}
	return ("\0");
}

t_norm2	*norm_sp1()
{
	t_norm2	*norm;

	norm = malloc(sizeof(t_norm2));
	norm->i = 0;
	norm->j = 0;
	norm->k = 0;
	norm->quotes = 0;
	norm->e = 0;
	norm->h = 0;
	norm->new_str = NULL;
	norm->dollar = NULL;
	norm->var = NULL;
	norm->valeur = NULL;
	return (norm);
}