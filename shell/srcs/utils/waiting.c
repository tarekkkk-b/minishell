/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:39:46 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/05 16:46:30 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	waiting(t_shell *shell)
{
	pid_t	id = 0;
	int 	temp;

	while(id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
		{
			if(shell->environ->exit == 0)
			{
				shell->environ->exit = WEXITSTATUS(temp);
				if (WTERMSIG(temp))
				{
					if (WTERMSIG(temp) == SIGINT)
					{
						shell->environ->exit = 130;
					}
					else if (WTERMSIG(temp) == SIGQUIT)
					{
						shell->environ->exit = 131;
					}
					else if(WTERMSIG(temp) == SIGSEGV)
					{
						shell->environ->exit = 139;
						write(2, "Segmentation Fault: 11\n", 23);
					}
				}
			}
		}
	}
	signalhandler(1);
}

int	waiting_heredoc(t_shell *shell, pid_t id)
{
	// pid_t 	id = 0;
	int 	temp;

	while(id != -1)
	{
		id = wait(&temp);
		if (id == shell->lastpid)
		{
			if(WEXITSTATUS(temp) == 1)
			{
				shell->environ->exit = 1;
				return (1);
			}
			if(shell->environ->exit == 0)
			{
				shell->environ->exit = WEXITSTATUS(temp);
				if (WTERMSIG(temp))
				{
					if (WTERMSIG(temp) == SIGINT)
					{
						shell->environ->exit = 130;
					}
					else if (WTERMSIG(temp) == SIGQUIT)
					{
						shell->environ->exit = 131;
					}
				}
			}
		}
	}
	signalhandler(1);
	return (0);
}
