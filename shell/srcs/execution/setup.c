/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:00:45 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/05 21:32:06 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	count_items(t_shell *shell, t_noding *traveler, t_counter *counter)
{
	(void)shell;
	counter->commands = 0;
	counter->inp_files = 0;
	counter->opt_files = 0;
	while (traveler && traveler->type != PIPES)
	{
		if (traveler->type == ARG)
			counter->commands++;
		if (traveler->type == OPT_FILE)
			counter->opt_files++;
		if (traveler->type == INP_FILE || traveler->type == DELIMITER)
			counter->inp_files++;
		traveler = traveler->next;
	}
}

void	setup_exec_struct(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*traveler2;

	int i = 0;
	int	command = 0;
	int opt_file = 0;
	int inp_file = 0;
	shell->counter = ft_malloc((sizeof(t_counter *) * (shell->parser->pipe_count + 2)), shell);
	shell->exec = ft_malloc((sizeof(t_exec *) * (shell->parser->pipe_count + 2)), shell);
	traveler = shell->parser->noding;
	while (traveler)
	{
		shell->counter[i] = ft_malloc(sizeof(t_counter), shell);
		shell->exec[i] = ft_malloc(sizeof(t_exec), shell);
		shell->exec[i]->fd[0] = -1;
		shell->exec[i]->fd[1] = -1;
		shell->exec[i]->heredoc_fd = -1;
		shell->exec[i]->cmdpath = NULL;
		command = 0;
		opt_file = 0;
		inp_file = 0;
		traveler2 = traveler;
		count_items(shell, traveler2, shell->counter[i]);
		shell->exec[i]->cmd = ft_malloc((sizeof(char *) * (shell->counter[i]->commands + 1)), shell);
		shell->exec[i]->inp_files = ft_malloc((sizeof(char *) * (shell->counter[i]->inp_files + 1)), shell);
		shell->exec[i]->inp_flags = ft_malloc((sizeof(int) * (shell->counter[i]->inp_files + 1)), shell);
		shell->exec[i]->opt_files = ft_malloc((sizeof(char *) * (shell->counter[i]->opt_files + 1)), shell);
		shell->exec[i]->opt_flags = ft_malloc((sizeof(int) * (shell->counter[i]->opt_files + 1)), shell);
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
		shell->exec[i]->cmd[command] = NULL;
		shell->exec[i]->opt_files[opt_file] = NULL;
		shell->exec[i]->inp_files[inp_file] = NULL;
		shell->exec[i]->opt_flags[opt_file] = -1;
		shell->exec[i]->inp_flags[inp_file] = -1;
		i++;
		if (traveler)
			traveler = traveler->next;
	}
	shell->exec[i] = NULL;
	shell->counter[i] = NULL;
}

char	**set_up_path(t_shell *shell)
{
	t_values	*locate;

	char	**path;
	locate = locate_node(shell->environ->env, "PATH");
	if (!locate)
		return (NULL);
	path = ft_split(locate->value, ':');
	path[0] = ft_strtrim(path[0], "PATH=", 1);
	return (path);
}
