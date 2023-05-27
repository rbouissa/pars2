



#include "minishell.h"
int	space_checking(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	freestack_last(t_list **stack)
{
	t_list	*temp;

	if (!*stack)
		return ;
	temp = *stack;
	while (*stack && (*stack)->next && (*stack)->token != 5)
	{
		(*stack) = (*stack)->next;
		free(temp->data);
		free(temp);
		temp = *stack;
	}
	*stack = (*stack)->next;
	if (temp->data)
		free(temp->data);
	free(temp);
}

int	file_numb(t_list *command)
{
	int	token;

	token = -2;
	if (command->next->token == 5 || command->next == NULL)
		return (token);
	if (command->next && command->token == 2)
	{
		token = open(command->next->data, O_CREAT | O_WRONLY, 0777);
		if (token == -1)
		{
			(write(2, "minishell: ", 11), perror(command->next->data));
			return (g_global->status = 1, -1);
		}
	}
	else if (command->next && command->token == 9)
	{
		token = open(command->next->data, O_CREAT | O_WRONLY | O_APPEND, 0777);
		if (token == -1)
		{
			write(2, "minishell: ", 11);
			perror(command->next->data);
			return (g_global->status = 1, -1);
		}
	}
	return (token);
}

int	her_pip(t_list *cmd)
{
	while (cmd)
	{
		if (cmd->token == 5)
			return (1);
		cmd = cmd->next;
	}
	return (0);
}

int	file_numb2(t_list *command)
{
	int	token;

	token = -2;
	if ((command->next->token == 5 || command->next == NULL))
		return (token);
	if (token != -2)
		close(token);
	if (command->next)
		token = open(command->next->data, O_RDONLY);
	if (token == -1)
	{
		write(2, "minishell: ", 11);
		perror(command->next->data);
		g_global->status = 1;
		return (-1);
	}
	return (token);
}