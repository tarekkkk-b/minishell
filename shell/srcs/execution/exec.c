/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:45:53 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/10 20:51:30 by tabadawi         ###   ########.fr       */
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

void	mass_close(t_shell *shell)
{
	int	i;

	i = 2;
	while (++i < 1025)
		ft_close(shell, &i);
}

int	inp_file_dup(t_exec	*exec)
{
	int	fd;
	int	flag;

	fd = -1;
	if (exec->inp_files && exec->inp_files[0])
	{
		flag = exec->inp_flags[get_arrlen(exec->inp_files) - 1];
		if (flag)
			fd = open("/tmp/.here_i_doc", O_RDONLY);
		else if (!flag)
			fd = open(exec->inp_files[get_arrlen(exec->inp_files) - 1], \
			O_RDONLY);
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			ft_close(exec->shell, &fd);
			return (1);
		}
	}
	return (0);
}

int	opt_file_dup(t_exec	*exec)
{
	int	fd;
	int	flag;

	fd = -1;
	if (exec->opt_files && exec->opt_files[0])
	{
		flag = exec->opt_flags[get_arrlen(exec->opt_files) - 1];
		if (flag)
			fd = open(exec->opt_files[get_arrlen(exec->opt_files) - 1], \
			O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (!flag)
			fd = open(exec->opt_files[get_arrlen(exec->opt_files) - 1], \
			O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		ft_close(exec->shell, &fd);
		return (1);
	}
	return (0);
}

void	closer(t_shell *shell, t_exec *exec, int f1, int f2)
{
	ft_close(shell, &exec->fd[WRITE_PIPE]);
	ft_close(shell, &exec->fd[READ_PIPE]);
	if (f1)
		ft_close(shell, &exec->heredoc_fd);
	if (f2)
		ft_close(shell, &shell->fd);
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

void	heredoc(t_shell *shell, t_exec *exec)
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
			return ;
	}
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
		if (i == 0)
			first_cmd(shell, shell->exec[i]);
		else if (shell->exec[i + 1])
			middle_cmd(shell, shell->exec[i]);
		else
			last_cmd(shell, shell->exec[i]);
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
		heredoc(shell, shell->exec[i]);
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
