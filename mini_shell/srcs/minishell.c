/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/22 20:01:05 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initializer(t_shell *shell)
{
	shell->environ = NULL;
	shell->exec = NULL;
	shell->parser = NULL;
}

void	count_items(t_shell *shell, t_noding *traveler, t_counter *counter)
{
	counter->commands = 0;
	counter->inp_files = 0;
	counter->opt_files = 0;
	while (traveler && traveler->type != PIPES)
	{
		if (traveler->type == ARGS)
			counter->commands++;
		if (traveler->type == OPT_FILE)
			counter->opt_files++;
		if (traveler->type == INP_FILE)
			counter->inp_files++;
		traveler = traveler->next;
	}
}

//inp:
//0 = inpfile
//1 = here_doc

//opt:
//0 = optfile
//1 = append

void	setup_exec_struct(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*traveler2;
	t_counter	*counter;

	int i = 0;
	int	command = 0;
	int opt_file = 0;
	int inp_file = 0;
	counter = ft_malloc(sizeof(t_counter));
	shell->exec = ft_malloc((sizeof(t_exec *) * shell->parser->noding + 2));
	traveler = shell->parser->noding;
	while (traveler)
	{
		command = 0;
		opt_file = 0;
		inp_file = 0;
		traveler2 = traveler;
		count_items(shell, traveler2, counter);
		shell->exec[i]->inp_files = ft_malloc((sizeof(char *) * counter->inp_files + 1));
		shell->exec[i]->cmd = ft_malloc((sizeof(char *) * counter->commands + 1));
		shell->exec[i]->inp_flags = ft_malloc((sizeof(int *) * counter->inp_files + 1));
		shell->exec[i]->opt_files = ft_malloc((sizeof(char *) * counter->opt_files + 1));
		shell->exec[i]->opt_flags = ft_malloc((sizeof(int *) * counter->opt_files + 1));
		while (traveler && traveler->type != PIPES)
		{
			if (traveler->type == ARG)
			{
				shell->exec[i]->cmd[command] = ft_strdup(traveler->value);
				command++;
			}
			if (traveler->type == OPT_REDIR)
			{
				shell->exec[i]->opt_files[opt_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->opt_flags[opt_file] = 0;
				opt_file++;
			}
			if (traveler->type == APPEND)
			{
				shell->exec[i]->opt_files[opt_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->opt_flags[opt_file] = 1;
				opt_file++;
			}
			if (traveler->type == INP_REDIR)
			{
				shell->exec[i]->inp_files[inp_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->inp_flags[inp_file] = 0;
				inp_file++;
			}
			if (traveler->type == HERE_DOC)
			{
				shell->exec[i]->inp_files[inp_file] = ft_strdup(traveler->next->value);
				shell->exec[i]->inp_flags[inp_file] = 1;
				inp_file++;
			}
			traveler = traveler->next;
		}
		ft_free((void **)&counter);
		i++;
		if (traveler)
			traveler = traveler->next;
	}
}

void	minishell(t_shell *shell)
{
	while (1)
	{
		signalhandler();
		ft_free((void **)&shell->environ->cwd);
		shell->environ->cwd = getcwd(NULL, 0);
		shell->str = readline("𝓯𝓻𝓮𝓪𝓴𝔂𝓼𝓱𝓮𝓵𝓵 > ");
		if (!shell->str)
			break ;
		if (shell->str[0] != '\0')
			add_history(shell->str);
		if (parsing_hub(shell, shell->str))
		{
			setup_exec_struct(shell);
			printf("tokenization succesful!\n");
		}
		else
			printf("tokenization failed successfully!\n");
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
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	minishell(&shell);
	mass_free(&shell, shell.environ->exit);
}
