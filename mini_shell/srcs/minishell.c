/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/11 19:47:43 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char *path;
	char *accpath;
	char *str;
	int	i;
	int	pipe_count;
	char ***pipes;
	char **one_command;
	(void)av;
	(void)env;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	while (1)
	{
		path = getcwd(NULL, 0);
		accpath = ft_strjoin(path, "> ");
		str = readline(accpath);
		if (str[0] != '\0')
			add_history(str);
		i = 0;
		pipe_count = 0;
		while (str[i])
		{
			if (str[ft_strlen(str) - 1] == '|')
			{
				printf("ERROR\n");
				exit(0);
			}
			if (str[i] == '|')
			{
				if (str[i + 1] != '|')
					pipe_count++;
				else
				{
					printf("ERROR\n");
					exit(0);
				}		
			}
			i++;
		}
		// printf("%d\n", pipe_count);
		pipes = malloc(sizeof(char **) * pipe_count + 1);
		free (str);
	}
}
