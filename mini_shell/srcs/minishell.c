/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/07 14:31:13 by ahaarij          ###   ########.fr       */
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
		rl.path = ft_strjoin(shell.environ->cwd, "> ");
		rl.str = readline(rl.path);
		// removed the exit thingies and added it to builtin
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
