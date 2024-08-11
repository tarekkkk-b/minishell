/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pt2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:55:56 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:59:08 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dupingcall(t_shell *shell, int i)
{
	if (i == 0)
		first_cmd(shell, shell->exec[i]);
	else if (shell->exec[i + 1])
		middle_cmd(shell, shell->exec[i]);
	else
		last_cmd(shell, shell->exec[i]);
}

void	first_cmd(t_shell *shell, t_exec *exec)
{
	inp_file_dup(exec);
	if (!opt_file_dup(exec))
	{
		dup2(exec->fd[WRITE_PIPE], STDOUT_FILENO);
		if (shell->exec[1])
			dup2(shell->fd, exec->fd[READ_PIPE]);
		ft_close(shell, &shell->fd);
	}
	closer(shell, exec, 1, 1);
}

void	middle_cmd(t_shell *shell, t_exec *exec)
{
	if (!inp_file_dup(exec))
	{
		dup2(shell->fd, STDIN_FILENO);
		ft_close(shell, &shell->fd);
	}
	if (!opt_file_dup(exec))
	{
		dup2(exec->fd[WRITE_PIPE], STDOUT_FILENO);
		dup2(shell->fd, exec->fd[READ_PIPE]);
	}
	closer(shell, exec, 0, 0);
}

void	last_cmd(t_shell *shell, t_exec *exec)
{
	if (!inp_file_dup(exec))
	{
		dup2(shell->fd, STDIN_FILENO);
		ft_close(shell, &shell->fd);
	}
	opt_file_dup(exec);
	closer(shell, exec, 0, 1);
}
