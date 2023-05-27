#include "minishell.h"








t_cmd	*split_mult_cmd(t_list **command, t_norm **norm, t_list **comm,
		t_cmd *list)
{
	while (*command != NULL)
	{
		if ((*command)->token == 5)
		{
			*command = (*command)->next;
			list = pipe_red(norm, NULL, comm, list);
		}
		else if ((*command)->token == 2 || (*command)->token == 3
				|| (*command)->token == 9)
		{
			if (in_out_red(norm, comm, command) == 1)
				break ;
			*command = (*command)->next->next;
		}
		else if ((*command)->token == 4)
			join_hrd_last(norm, command);
		else
		{
			join_cmd(norm, command);
			*command = (*command)->next;
		}
	}
	return (list);
}

t_cmd	*split_to_commands(t_list *comm)
{
	t_list	*command;
	t_cmd	*list;
	t_norm	*norm;

	norm = init_norm();
	command = comm;
	list = NULL;
	if (!her_pip(command))
		list = split_one_cmd(&command, &norm, &comm, list);
	else
	{
		list = split_mult_cmd(&command, &norm, &comm, list);
		if (norm->hrd != NULL)
			list = herd_pi(&norm, list);
		else
			list = no_herd_pi(&norm, list);
		free(norm->hrd);
		free(norm->cmd);
	}
	free(norm->spliter);
	ft_free_cmd(comm);
	free(norm);
	return (list);
}
