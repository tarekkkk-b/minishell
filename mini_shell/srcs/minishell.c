/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/20 18:23:11 by tabadawi         ###   ########.fr       */
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
		free(shell.environ->cwd);
		shell.environ->cwd = getcwd(NULL, 0);
		rl.str = readline("𝓯𝓻𝓮𝓪𝓴𝔂𝓼𝓱𝓮𝓵𝓵 > ");
		if(!rl.str)
			break ;
			// if(builtin_exit(rl))
			// 	return (1);
		// just adding this here to test :)
		// if(builtin_check(rl, &shell) == 1)
		// 	return (1);
		if (rl.str[0] != '\0')
			add_history(rl.str);
		parsing_hub(&shell, rl.str);
		if (shell.parser->noding)
		{
			t_noding *temp;
			t_noding *temp2;
			temp = shell.parser->noding;
			while (temp)
			{
				temp2 = temp->next;
				free (temp->value);
				free (temp);
				temp = temp2;
			}
			free (shell.parser);
		}
		free (rl.str);
		free(shell.environ->cwd);
	}
	t_values *tempe;
	t_values *tempe2;
	if (shell.environ->env)
	{
		tempe = shell.environ->env;
		while (tempe)
		{
			tempe2 = tempe->next;
			free (tempe->value);
			free(tempe->key);
			free(tempe->string);
			free (tempe);
			tempe = tempe2;
		}
		printf("cwd %s\n", shell.environ->cwd);
		free(shell.environ->cwd);
		shell.environ->cwd = NULL;
		printf("owd %s\n", shell.environ->owd);
		free(shell.environ->owd);
		shell.environ->owd = NULL;
		free(shell.environ);
	}
	// t_noding *temp;
	// t_noding *temp2;
	// temp = shell.parser->noding;
	// while (temp)
	// {
	// 	temp2 = temp->next;
	// 	free (temp->value);
	// 	free (temp);
	// 	temp = temp2;
	// }
	// free (shell.parser);
}
