#include "parsing.h"

t_file	*full_file(t_list *cmd)
{
	t_list *command;
	t_file *list;
	int check;
	check = 0;
	int token;
	token = 0;
	command = cmd;
	while (command->next)
	{
		if ((command->token == 2 || command->token == 3))
		{
			if (command->token == 2)
			{
				token = open(command->next->data, O_CREAT | O_RDONLY);
				if (check == 0)
				{
					list = ft_lstnew_file(command->next->data, token, -2);
					check = 1;
				}
			}
			else
			{
				token = open(command->next->data, O_WRONLY);
				if (check == 0)
				{
					list = ft_lstnew_file(command->next->data, token, -2);
					check = 1;
				}
				else
					ft_lstadd_back_new(&list,
										ft_lstnew_file(command->next->data, -2,
												token));
			}
			if (token == -1)
			{
				printf("%s", command->next->data);
				printf(":No such file or directory\n");
			}
		}
		else
			token = -2;
		command = command->next;
	}
	return (list);
}