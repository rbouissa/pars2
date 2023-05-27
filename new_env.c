
#include "minishell.h"




void	free_some(t_norm2 **norm)
{
	if ((*norm)->e == 1)
	{
		free((*norm)->var);
		(*norm)->var = NULL;
	}
	if ((*norm)->h)
		free((*norm)->valeur);
}

char	*do_all_work(t_norm2 **norm, char *str, t_mini **env, char *new_str)
{
	while (str[(*norm)->i])
	{
		(*norm)->e = 0;
		(*norm)->h = 0;
		if (str[(*norm)->i] == '\'' && (*norm)->quotes == no_quotes)
			(*norm)->quotes = isingle_quotes;
		else if (str[(*norm)->i] == '\"' && (*norm)->quotes == no_quotes)
			(*norm)->quotes = idouble_quotes;
		else if (str[(*norm)->i] == '\"' && (*norm)->quotes == idouble_quotes)
			(*norm)->quotes = no_quotes;
		else if (str[(*norm)->i] == '\'' && (*norm)->quotes == isingle_quotes)
			(*norm)->quotes = no_quotes;
		if (str[(*norm)->i] == '$' && (*norm)->quotes != isingle_quotes
			&& (str[(*norm)->i - 1] != '<' || str[(*norm)->i - 2] != '<'))
			new_str = lite_expand(norm, str, env, new_str);
		else
		{
			new_str = ft_strjoin(new_str,
									(char[]){str[(*norm)->i], 0});
			(*norm)->i++;
		}
		free_some(norm);
	}
	return (new_str);
}
char	*new_expand(char *str, t_mini *env)
{
	t_norm2	*norm;
	char	*new_str;

	norm = norm_sp1();
	new_str = NULL;
	norm->dollar = malloc(2);
	norm->dollar[0] = '$';
	norm->dollar[1] = '\0';
	new_str = do_all_work(&norm, str, &env, new_str);
	free(norm->var);
	free(norm->dollar);
	if (norm->quotes == idouble_quotes || norm->quotes == isingle_quotes)
	{
		ft_write("syntax error exepected quote");
		return (free(norm), NULL);
	}
	else
		return (free(norm), new_str);
}
