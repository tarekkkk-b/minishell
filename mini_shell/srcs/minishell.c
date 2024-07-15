/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/15 12:43:10 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		shell.environ->cwd = getcwd(NULL, 0);
		rl.path = ft_strjoin(shell.environ->cwd, "> ");
		rl.str = readline(rl.path);
		if(!rl.str)
			if(builtin_exit(rl))
				return (1);
		// just adding this here to test :)
		if(builtin_check(rl, &shell) == 1)
			return (1);
		if (rl.str[0] != '\0')
			add_history(rl.str);
		recieve_str(&shell, rl.str);
		free(rl.path);
		free (rl.str);
	}
}
