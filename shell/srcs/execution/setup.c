/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 12:00:45 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/11 12:55:29 by ahaarij          ###   ########.fr       */
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

void	alloc_struct(t_shell *shell, t_exec **exec, int i)
{
	(*exec)->fd[0] = -1;
	(*exec)->fd[1] = -1;
	(*exec)->heredoc_fd = -1;
	(*exec)->cmdpath = NULL;
	(*exec)->cmd = ft_malloc((sizeof(char *) * \
	(shell->counter[i]->commands + 1)), shell);
	(*exec)->inp_files = ft_malloc((sizeof(char *) * \
	(shell->counter[i]->inp_files + 1)), shell);
	(*exec)->inp_flags = ft_malloc((sizeof(int) * \
	(shell->counter[i]->inp_files + 1)), shell);
	(*exec)->opt_files = ft_malloc((sizeof(char *) * \
	(shell->counter[i]->opt_files + 1)), shell);
	(*exec)->opt_flags = ft_malloc((sizeof(int) * \
	(shell->counter[i]->opt_files + 1)), shell);
}

void	set(char **str, int *i, int	*arr, t_noding *trav)
{
	if (!arr)
		str[(*i)] = ft_strdup(trav->value);
	else
		str[(*i)] = ft_strdup(trav->next->value);
	if (arr && (trav->type == OPT_REDIR || trav->type == OPT_REDIR))
		arr[(*i)] = 0;
	else if (arr && (trav->type == APPEND || trav->type == HERE_DOC))
		arr[(*i)] = 1;
	(*i)++;
}

t_noding	*set_loop(t_exec **exec, t_noding *traveler)
{
	int	command;
	int	opt_file;
	int	inp_file;

	command = 0;
	opt_file = 0;
	inp_file = 0;
	while (traveler && traveler->type != PIPES)
	{
		if (traveler->type == ARG)
			set((*exec)->cmd, &command, NULL, traveler);
		if (traveler->type == OPT_REDIR || traveler->type == APPEND)
			set((*exec)->opt_files, &opt_file, (*exec)->opt_flags, traveler);
		if (traveler->type == INP_REDIR || traveler->type == HERE_DOC)
			set((*exec)->inp_files, &inp_file, (*exec)->inp_flags, traveler);
		traveler = traveler->next;
	}
	(*exec)->cmd[command] = NULL;
	(*exec)->opt_files[opt_file] = NULL;
	(*exec)->inp_files[inp_file] = NULL;
	(*exec)->opt_flags[opt_file] = -1;
	(*exec)->inp_flags[inp_file] = -1;
	return (traveler);
}

void	setup_exec_struct(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*traveler2;
	int			i;

	i = 0;
	shell->counter = ft_malloc((sizeof(t_counter *) * \
	(shell->parser->pipe_count + 2)), shell);
	shell->exec = ft_malloc((sizeof(t_exec *) * \
	(shell->parser->pipe_count + 2)), shell);
	traveler = shell->parser->noding;
	while (traveler)
	{
		traveler2 = traveler;
		shell->counter[i] = ft_malloc(sizeof(t_counter), shell);
		count_items(shell, traveler2, shell->counter[i]);
		shell->exec[i] = ft_malloc(sizeof(t_exec), shell);
		alloc_struct(shell, &shell->exec[i], i);
		traveler = set_loop(&shell->exec[i], traveler);
		i++;
		if (traveler)
			traveler = traveler->next;
	}
	shell->exec[i] = NULL;
	shell->counter[i] = NULL;
}
