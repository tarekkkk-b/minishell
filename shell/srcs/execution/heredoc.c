/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:56:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:58:04 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_heredoc(t_exec *exec)
{
	int	i;

	i = -1;
	while (exec->inp_files[++i])
		if (exec->inp_flags[i])
			return (1);
	return (0);
}

int	heredoc(t_shell *shell, t_exec *exec, pid_t id, int i)
{
	if (check_heredoc(exec))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		shell->child = fork();
		if (!shell->child)
		{
			signal(SIGINT, do_nothing);
			collect_heredoc(shell, i);
			closer(shell, exec, 1, 1);
			mass_free(shell, 0);
		}
		if (waiting_heredoc(shell, id) == 1)
			return (1);
	}
	return (0);
}

char	*heredoc_loop(t_shell *shell, t_exec *exec, int i)
{
	char	*str;

	str = readline("> ");
	while (1)
	{
		if (g_signalnumber == SIGINT)
		{
			closer(shell, exec, 1, 1);
			mass_free(shell, 1);
		}
		if (!str || (!ft_strcmp(str, exec->inp_files[i])))
			break ;
		str = ft_strjoin(str, "\n", 1);
		ft_putstr_fd(str, exec->heredoc_fd);
		ft_free((void **)&str);
		str = readline("> ");
	}
	return (str);
}

void	collect_heredoc(t_shell *shell, int index)
{
	int		i;
	char	*str;

	i = -1;
	if (!shell->exec[index]->inp_files || !shell->exec[index]->inp_files[0])
		mass_free(shell, 1);
	while (shell->exec[index]->inp_files[++i])
	{
		if (shell->exec[index]->inp_flags[i])
		{
			shell->exec[index]->heredoc_fd = open("/tmp/.here_i_doc", O_CREAT \
			| O_TRUNC | O_WRONLY, 0620);
			if (shell->exec[index]->heredoc_fd == -1)
				mass_free(shell, 1);
			str = heredoc_loop(shell, shell->exec[index], i);
			ft_close(shell, &shell->exec[index]->heredoc_fd);
		}
		if (!str)
		{
			closer(shell, shell->exec[index], 0, 0);
			mass_free(shell, 0);
		}
	}
}
