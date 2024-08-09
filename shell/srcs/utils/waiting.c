/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:39:46 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/09 17:11:30 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_checks(t_shell *shell, int temp)
{
	if (WTERMSIG(temp) == SIGINT)
		shell->environ->exit = 130;
	else if (WTERMSIG(temp) == SIGQUIT)
		shell->environ->exit = 131;
	else if (WTERMSIG(temp) == SIGSEGV)
	{
		shell->environ->exit = 139;
		write(2, "Segmentation Fault: 11\n", 23);
	}
}

void	waiting(t_shell *shell)
{
	pid_t	id;
	int		temp;

	id = 0;
	temp = 0;
	while (id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
		{
			if (shell->environ->exit == 0)
			{
				shell->environ->exit = WEXITSTATUS(temp);
				if (WTERMSIG(temp))
					sig_checks(shell, temp);
			}
		}
	}
	signalhandler(1);
}

int	waiting_heredoc(t_shell *shell, pid_t id)
{
	int	temp;

	while (id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
		{
			if (WEXITSTATUS(temp) == 1)
			{
				shell->environ->exit = 1;
				return (1);
			}
			if (shell->environ->exit == 0)
			{
				shell->environ->exit = WEXITSTATUS(temp);
				if (WTERMSIG(temp))
					sig_checks(shell, temp);
			}
		}
	}
	signalhandler(1);
	return (0);
}
