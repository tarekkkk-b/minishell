/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/27 20:35:36 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	just_test(t_readline rl)
{
	write(0, "exit\n", 5);
	if(kill(getpid(), 0) == 0)
	{
		free(rl.path);
		free(rl.str);
		return(1);
	}
	return (0);
}
// you can change theh struct name rl looks kinda ugly and reminds me of rocket league
// thats all
int	main(int ac, char **av, char **env)
{
	t_readline	rl;
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
		rl.path = ft_strjoin(shell.environ->cwd, "> ");
		rl.str = readline(rl.path);
		if(!rl.str)		// this if condition was needed.
			if(just_test(rl) == 1)
				return(1);
		if(strncmp(rl.str, "exit", 4) == 0)
			if(just_test(rl) == 1)
				return (1);
		if (rl.str[0] != '\0')
			add_history(rl.str);
		recieve_str(&shell, rl.str);
		free(rl.path);
		free (rl.str);
	}
}
// we didnt free path ever btw
