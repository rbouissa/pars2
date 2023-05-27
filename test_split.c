
#include "minishell.h"

t_list	*our_list(t_nor_sp **norm, t_list *s, char *str)
{
	while (str[(*norm)->i])
	{
		(*norm)->k = (*norm)->i;
		(*norm)->i = count_nosplit(norm, str);
		if ((*norm)->i - (*norm)->k != 0)
		{
			fill_struct(norm, &s, str);
			free((*norm)->node);
			(*norm)->node = NULL;
		}
		else
		{
			(*norm)->k = (*norm)->i;
			(*norm)->j = 0;
			(*norm)->j = count_spl(norm, str);
			if ((*norm)->j != 0)
			{
				fill_struct2(norm, &s, str);
				free((*norm)->st);
				(*norm)->st = NULL;
			}
		}
	}
	return (s);
}

t_list	*ft_split_them(char *str)
{
	t_list		*s;
	t_nor_sp	*norm;

	norm = norm_sp();
	s = NULL;
	s = our_list(&norm, s, str);
	free(norm);
	return (s);
}
