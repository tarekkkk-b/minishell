/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/19 21:36:45 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char 		*path;
	char 		*str;
	t_shell		shell;
	(void)av;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	t_values	*temp;
	temp = shell.environ->env;
	while (temp)
	{
		printf("%s\n", temp->string);
		temp = temp->next;
	}
	while (1)
	{
		path = ft_strjoin(shell.environ->cwd, "> ");
		str = readline(path);
		if (str[0] != '\0')
			add_history(str);
		free (str);
	}
}
