/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/25 12:53:46 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	just_test(void)
{
	write(0, "exit\n", 5);
	if(kill(getpid(), 0) == 0)
		return(1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char 		*path;
	char 		*str;
	t_shell		shell;
	shell.environ = NULL;
	(void)av;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	while (1)
	{
		signalhandler();
		path = ft_strjoin(shell.environ->cwd, "> ");
		str = readline(path);
		if(strncmp(str, "exit", 4) == 0)
			if(just_test() == 1)
			{
				free(str);
				return (1);
			}
		if (str[0] != '\0')
			add_history(str);
		recieve_str(&shell, str);
		free (str);
	}
}
