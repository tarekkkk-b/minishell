/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:45:53 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/11 12:58:59 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	closer(t_shell *shell, t_exec *exec, int f1, int f2)
{
	ft_close(shell, &exec->fd[WRITE_PIPE]);
	ft_close(shell, &exec->fd[READ_PIPE]);
	if (f1)
		ft_close(shell, &exec->heredoc_fd);
	if (f2)
		ft_close(shell, &shell->fd);
}

void	process(t_shell *shell, int i)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	shell->child = fork();
	if (shell->child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (!(mass_check(shell->exec[0]->cmd[0]) && !shell->exec[1]))
			dupingcall(shell, i);
		if (shell->exec[i]->cmd[0])
		{
			if (builtin_check(shell, i, 1) != 0)
				execution(shell, i);
		}
		mass_free(shell, shell->environ->exit);
		unlink("/tmp/.here_i_doc");
	}
	builtin_check(shell, i, 0);
	ft_close(shell, &shell->fd);
	shell->fd = dup(shell->exec[i]->fd[READ_PIPE]);
	closer(shell, shell->exec[i], 1, 0);
}

void	exec_loop(t_shell *shell)
{
	int		i;
	pid_t	id;

	id = 0;
	i = 0;
	shell->fd = -1;
	while (shell->exec[i])
	{
		if (shell->exec[i + 1])
			pipe(shell->exec[i]->fd);
		if (heredoc(shell, shell->exec[i], id, i))
			return ;
		if (check_inp_files(shell, i) && check_opt_files(shell, i))
			process(shell, i);
		else
		{
			if (shell->exec[i + 1])
			{
				shell->fd = dup(shell->exec[i]->fd[READ_PIPE]);
				closer(shell, shell->exec[i], 0, 0);
			}
		}
		i++;
	}
	ft_close(shell, &shell->fd);
}

void	exec(t_shell *shell, int index, char *cmd)
{
	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK) == -1)
		{
			ft_putstr_fd(cmd, 1);
			ft_putstr_fd(": Permission denied\n", 1);
			shell->environ->exit = 126;
			mass_free(shell, 126);
		}
		else
			execve(cmd, shell->exec[index]->cmd, shell->environ->environment);
	}
}

void	execution(t_shell *shell, int index)
{
	int	i;

	i = -1;
	shell->environ->environment = arr(shell->environ->env, shell);
	shell->environ->path = set_up_path(shell);
	exec(shell, index, shell->exec[index]->cmd[0]);
	if (shell->environ->path)
	{
		while (shell->environ->path[++i] && shell->exec[index]->cmd[0])
		{
			shell->exec[index]->cmdpath = ft_strjoin2(shell->environ->path[i], \
			"/", shell->exec[index]->cmd[0]);
			exec(shell, index, shell->exec[index]->cmdpath);
			ft_free((void **)&shell->exec[index]->cmdpath);
		}
		ft_putstr_fd(shell->exec[index]->cmd[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		ft_close(shell, &shell->fd);
		mass_free(shell, 127);
	}
}
