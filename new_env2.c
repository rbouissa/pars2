




#include "minishell.h"

void	for_dollar(t_norm2 **norm, char *str)
{
	while (str[(*norm)->i] == '$')
	{
		(*norm)->i++;
		(*norm)->e++;
	}
}

void	alloc_built(t_norm2 **norm, char *str)
{
	(void)str;
	(*norm)->var = malloc(2);
	(*norm)->var[0] = '?';
	(*norm)->var[1] = '\0';
	(*norm)->i++;
	(*norm)->h++;
}

void	alloc_simple(t_norm2 **norm, char *str)
{
	(*norm)->k = (*norm)->i;
	while (!find_spliter1(str[(*norm)->k], "|>< \t\n\'\""))
	{
		(*norm)->k++;
		(*norm)->j++;
	}
	if ((*norm)->var)
		free((*norm)->var);
	(*norm)->var = malloc((*norm)->j + 1);
	(*norm)->k = (*norm)->i;
	(*norm)->j = 0;
	while (!find_spliter1(str[(*norm)->k], "|>< \t\n\'\""))
	{
		(*norm)->var[(*norm)->j] = str[(*norm)->k];
		(*norm)->k++;
		(*norm)->j++;
	}
	(*norm)->var[(*norm)->j] = '\0';
	(*norm)->k = 0;
}

char	*join_character(t_norm2 **norm, char *str, t_mini **env, char *new_str)
{
	(void)str;
	(*norm)->valeur = finnd_valeur((*env), (*norm)->var);
	new_str = ft_strjoin(new_str, (*norm)->valeur);
	while (!find_spliter1(str[(*norm)->i], "|>< \t\n\'\""))
		(*norm)->i++;
	return (new_str);
}

char	*lite_expand(t_norm2 **norm, char *str, t_mini **env, char *new_str)
{
	for_dollar(norm, str);
	if (str[(*norm)->i] == '?')
		alloc_built(norm, str);
	else
		alloc_simple(norm, str);
	if (((*norm)->e % 2 != 0 && (*norm)->e > 2) || ((*norm)->e == 1
			&& !str[(*norm)->i] && (*norm)->h != 1))
		new_str = ft_strjoin(new_str, (*norm)->dollar);
	new_str = join_character(norm, str, env, new_str);
	
	return (new_str);
}