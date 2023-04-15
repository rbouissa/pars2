#include "parsing.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ther_are_pipe(char *str)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		// if (str[i] == 34 || str[i] == 39)
		// {
		//     printf("jgkjg\n");
		// 	quotes = str[i];
		// 	i++;
		// 	while (str[i] && (str[i+1] != quotes))
		// 		i++;
		// }
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char *str;
	char **s;
	t_list *cmd;
	t_cmd *commands;
	t_file *comd;
	int i;
	int j;
	int k;

	i = 0;

	while (1)
	{
		str = readline("minishell>");
		//add expanding variables
		if (str[0])
		{
			j = check_eroor(str);
			k = check_string(str);
			// s = split_command(str);
			if (j && k)
			{
				cmd = ft_split_them(str);
				//printf("%d\n",ther_are_pipe(str));

				
				// if there is a pipe use the linked list of t_cmd els ejust use the old on t_list
				// if (ther_are_pipe(str))

				commands = split_to_commands(cmd, str);
				//printf("kkk\n");
				// if(commands->cmd[0]==NULL)
				// printf("yes\n");
				while (commands)
				{
					// 	while (commands->cmd[i])
					// 	{
					// 		printf("%s\n", commands->cmd[i]);
					// 		i++;
					// 	}
					 i = 0;
					 if (commands->cmd[i] == NULL)
						printf("%s\n", commands->cmd[i]);
					while (commands->cmd[i])
					{
						printf("command==");
						printf("%s\n", commands->cmd[i]);
						i++;
					}
					i = 0;
					if (commands->herdoc[i] == NULL)
						printf("%s\n", commands->herdoc[i]);
					else
					{
						while (commands->herdoc[i])
						{
							printf("herdoc==");
							printf("%s\n", commands->herdoc[i]);
							i++;
						}
					}
					 printf("%d\n", commands->infile);
					 printf("%d\n", commands->outfile);
					// printf("%d\n", commands->herdoc_token);
					commands = commands->next;
					//printf("kllko\n");
				}
			}
		}
		//}
		add_history(str);
		free(str);
	}
}