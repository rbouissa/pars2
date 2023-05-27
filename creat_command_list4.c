


#include"minishell.h"

int	in_out_red(t_norm **norm, t_list **comm, t_list **command)
{
	(void)comm;
	if ((*command)->token == 2 || (*command)->token == 9)
		(*norm)->token = file_numb(*command);
	else if ((*command)->token == 3)
		(*norm)->token2 = file_numb2(*command);
	if ((*norm)->token == -1 || (*norm)->token2 == -1)
		return (1);
	return (0);
}

t_cmd	*split_one_cmd(t_list **command, t_norm **norm, t_list **comm,
		t_cmd *list)
{
	one_cmd_splited(norm, command, comm);
	if ((*norm)->hrd != NULL)
		list = one_cmd_checking(norm, list);
	else
		list = no_herdoc_check(norm, list);
	free((*norm)->cmd);
	free((*norm)->hrd);
	return (list);
}

void	redifine_norm(t_norm **norm)
{
	(*norm)->token = -2;
	(*norm)->token2 = -2;
	free((*norm)->cmd);
	free((*norm)->hrd);
	(*norm)->cmd = NULL;
	(*norm)->hrd = NULL;
}

t_cmd	*pipe_red(t_norm **norm, t_list **command, t_list **comm, t_cmd *list)
{
	(void)command;
	(void)comm;
	freestack_last(comm);
	if ((*norm)->hrd != NULL)
		list = her11(norm, list);
	else
		list = her12(norm, list);
	redifine_norm(norm);
	return (list);
}

void	join_hrd_last(t_norm **norm, t_list **command)
{
	join_hrd(norm, &(*command)->next);
	*command = (*command)->next->next;
}