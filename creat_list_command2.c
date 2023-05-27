






#include "minishell.h"
t_norm	*init_norm()
{
	t_norm	*norm;

	norm = malloc(sizeof(t_norm));
	norm->cmd = NULL;
	norm->hrd = NULL;
	norm->herdoc = NULL;
	norm->full_cmd = NULL;
	norm->check = 0;
	norm->spliter = malloc(2);
	norm->spliter[0] = 19;
	norm->spliter[1] = '\0';
	norm->token = -2;
	norm->token2 = -2;
	return (norm);
}

void	one_cmd_splited(t_norm **norm, t_list **command, t_list **comm)
{
	(void)comm;
	while (*command)
	{
		if ((*command)->token == 2 || (*command)->token == 3
			|| (*command)->token == 9)
		{
			in_out_red(norm, NULL, command);
			if ((*norm)->token == -1 || (*norm)->token2 == -1)
				break ;
			*command = (*command)->next->next;
		}
		else if ((*command)->token == 4)
		{
			*command = (*command)->next;
			(*norm)->hrd = ft_strjoin((*norm)->hrd, (*norm)->spliter);
			(*norm)->hrd = ft_strjoin((*norm)->hrd, (*command)->data);
			*command = (*command)->next;
		}
		else
		{
			(*norm)->cmd = ft_strjoin((*norm)->cmd, (*norm)->spliter);
			(*norm)->cmd = ft_strjoin((*norm)->cmd, (*command)->data);
			*command = (*command)->next;
		}
	}
}

t_cmd	*one_cmd_checking(t_norm **norm, t_cmd *list)
{
	if ((*norm)->cmd == NULL)
	{
		(*norm)->full_cmd = malloc(sizeof(char *));
		(*norm)->full_cmd[0] = 0;
		list = ft_lstnew_new((*norm)->full_cmd, (*norm)->token, (*norm)->token2,
				ft_split((*norm)->hrd, 19), 1);
		(*norm)->token = -2;
		(*norm)->token2 = -2;
	}
	else
	{
		list = ft_lstnew_new(ft_split((*norm)->cmd, 19), (*norm)->token,
				(*norm)->token2, ft_split((*norm)->hrd, 19), 1);
		(*norm)->token = -2;
		(*norm)->token2 = -2;
	}
	return (list);
}
t_cmd	*no_herdoc_check(t_norm **norm, t_cmd *list)
{
	(*norm)->herdoc = malloc(sizeof(char *));
	(*norm)->herdoc[0] = 0;
	list = ft_lstnew_new(ft_split((*norm)->cmd, 19), (*norm)->token,
			(*norm)->token2, (*norm)->herdoc, -2);
	(*norm)->token = -2;
	(*norm)->token2 = -2;
	return (list);
}

t_cmd	*herd_pi(t_norm **norm, t_cmd *list)
{
	if ((*norm)->cmd != NULL)
		ft_lstadd_back_new(&list, ft_lstnew_new(ft_split((*norm)->cmd, 19),
					(*norm)->token, (*norm)->token2, ft_split((*norm)->hrd, 19),
					1));
	else
	{
		(*norm)->full_cmd = malloc(sizeof(char *));
		(*norm)->full_cmd[0] = 0;
		ft_lstadd_back_new(&list, ft_lstnew_new((*norm)->full_cmd,
					(*norm)->token, (*norm)->token2, ft_split((*norm)->hrd, 19),
					1));
	}
	(*norm)->token = -2;
	(*norm)->token2 = -2;
	return (list);
}