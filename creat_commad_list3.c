





#include "minishell.h"
t_cmd	*no_herd_pi(t_norm **norm, t_cmd *list)
{
	(*norm)->herdoc = malloc(sizeof(char *));
	(*norm)->herdoc[0] = 0;
	ft_lstadd_back_new(&list, ft_lstnew_new(ft_split((*norm)->cmd, 19),
				(*norm)->token, (*norm)->token2, (*norm)->herdoc, 1));
	(*norm)->token = -2;
	(*norm)->token2 = -2;
	return (list);
}

t_cmd	*her11(t_norm **norm, t_cmd *list)
{
	if ((*norm)->cmd != NULL)
	{
		ft_lstadd_back_new(&list,
							ft_lstnew_new(ft_split((*norm)->cmd,
													19),
											(*norm)->token,
											(*norm)->token2,
											ft_split((*norm)->hrd,
													19),
											1));
	}
	else
	{
		(*norm)->full_cmd = malloc(sizeof(char *));
		(*norm)->full_cmd[0] = 0;
		ft_lstadd_back_new(&list,
							ft_lstnew_new((*norm)->full_cmd,
											(*norm)->token,
											(*norm)->token2,
											ft_split((*norm)->hrd,
													19),
											1));
	}
	return (list);
}

t_cmd	*her12(t_norm **norm, t_cmd *list)
{
	(*norm)->herdoc = malloc(sizeof(char *));
	(*norm)->herdoc[0] = 0;
	ft_lstadd_back_new(&list,
						ft_lstnew_new(ft_split((*norm)->cmd,
												19),
										(*norm)->token,
										(*norm)->token2,
										(*norm)->herdoc,
										1));
	return (list);
}

void	join_hrd(t_norm **norm, t_list **command)
{
	(*norm)->hrd = ft_strjoin((*norm)->hrd, (*norm)->spliter);
	(*norm)->hrd = ft_strjoin((*norm)->hrd, (*command)->data);
}

void	join_cmd(t_norm **norm, t_list **command)
{
	(*norm)->cmd = ft_strjoin((*norm)->cmd, (*norm)->spliter);
	(*norm)->cmd = ft_strjoin((*norm)->cmd, (*command)->data);
}