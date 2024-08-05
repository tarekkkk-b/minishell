/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/05 14:14:25 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initializer(t_shell *shell)
{
	shell->environ = NULL;
	shell->exec = NULL;
	shell->parser = NULL;
	shell->counter = NULL;
	shell->fd = -1;
	shell->lastpid = -1;
}

void	waiting(t_shell *shell)
{
	pid_t	id = 0;
	int 	temp;

	while(id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
			if(shell->environ->exit == 0)
			{
				shell->environ->exit = WEXITSTATUS(temp);
				if (WTERMSIG(temp))
				{
					if (WTERMSIG(temp) == SIGINT)
						shell->environ->exit = 130;
					else if (WTERMSIG(temp) == SIGQUIT)
						shell->environ->exit = 131;
					else if(WTERMSIG(temp) == SIGSEGV)
					{
						shell->environ->exit = 139;
						write(2, "Segmentation Fault: 11\n", 23);
					}
				}

			}
	}
	signalhandler(1);
}

void	do_nothing(int sig)
{
	g_signalnumber = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	// exit(0);
}

void	minishell(t_shell *shell)
{
	if (!isatty(0))
		rl_outstream = stdin;
	while (1)
	{
		signalhandler(1);
		ft_free((void **)&shell->environ->cwd);
		shell->environ->cwd = getcwd(NULL, 0);
		if (g_signalnumber != SIGINT)
			shell->str = readline("𝓯𝓻𝓮𝓪𝓴𝔂𝓼𝓱𝓮𝓵𝓵 > ");
		else
			shell->str = readline(NULL);
		if(g_signalnumber == SIGINT)
			shell->environ->exit = 1;
		g_signalnumber = -1;
		if (!shell->str)
			break ;
		//USE FT_STRCMP
		if (strcmp(shell->str, "") == 0)
			continue ;
		if (shell->str[0] != '\0')
			add_history(shell->str);
		if (parsing_hub(shell, shell->str))
		{
			setup_exec_struct(shell);
			exec_loop(shell);
			free_exec(shell);
		}
		waiting(shell);
		free_tokenization(shell);
		free (shell->str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		shell;

	shell.environ = NULL;
	(void)av;
	if (ac != 1)
		return (-1);
	initializer(&shell);
	create_env(env, &shell);
	minishell(&shell);
	mass_free(&shell, shell.environ->exit);
}
