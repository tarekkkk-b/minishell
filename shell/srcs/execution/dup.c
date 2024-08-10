/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:50:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/10 16:05:59 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close(t_shell *shell, int *fd)
{
	if ((*fd) >= 0)
		if (close(*fd) == -1)
			mass_free(shell, 1);
	(*fd) = -1;
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	i = -1;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (str1[++i])
			if (str1[i] != str2[i])
				return (1);
	}
	else
		return (1);
	return (0);
}

void	inp_dup(t_shell *shell, int index, int temp_fd)
{
	int	fd;
	int	flag;
	int	len;

	fd = -1;
	if (shell->exec[index]->inp_files && shell->exec[index]->inp_files[0])
	{
		len = get_arrlen(shell->exec[index]->inp_files) - 1;
		flag = shell->exec[index]->inp_flags[len];
		if (flag)
			fd = open("/tmp/.here_i_doc", O_RDONLY);
		else if (!flag)
			fd = open(shell->exec[index]->inp_files[len], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		ft_close(shell, &fd);
	}
	else if (index != 0)
		dup2(temp_fd, STDIN_FILENO);
	ft_close(shell, &shell->exec[index]->fd[READ_PIPE]);
}

void	opt_dup(t_shell *shell, int index)
{
	int	fd;
	int	flag;
	int	len;

	fd = -1;
	if (shell->exec[index]->opt_files && shell->exec[index]->opt_files[0])
	{
		len = get_arrlen(shell->exec[index]->opt_files) - 1;
		flag = shell->exec[index]->opt_flags[len];
		if (flag)
			fd = open(shell->exec[index]->opt_files [len], O_CREAT \
			| O_APPEND | O_WRONLY, 0644);
		else if (!flag)
			fd = open(shell->exec[index]->opt_files[len], O_CREAT \
			| O_TRUNC | O_WRONLY, 0644);
	}
	if (fd != -1)
		dup2(fd, STDOUT_FILENO);
	ft_close(shell, &fd);
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
			str = readline("> ");
			while (1)
			{
				if (g_signalnumber == SIGINT)
				{
					ft_close(shell, &shell->fd);
					ft_close(shell, &shell->exec[index]->heredoc_fd);
					ft_close(shell, &shell->exec[index]->fd[WRITE_PIPE]);
					ft_close(shell, &shell->exec[index]->fd[READ_PIPE]);
					mass_free(shell, 1);
				}
				if (!str || (!ft_strcmp(str, shell->exec[index]->inp_files[i])))
					break ;
				str = ft_strjoin(str, "\n", 1);
				ft_putstr_fd(str, shell->exec[index]->heredoc_fd);
				ft_free((void **)&str);
				str = readline("> ");
			}
			ft_close(shell, &shell->exec[index]->heredoc_fd);
		}
		if (!str)
		{
			ft_close(shell, &shell->exec[index]->fd[WRITE_PIPE]);
			ft_close(shell, &shell->exec[index]->fd[READ_PIPE]);
			mass_free(shell, 0);
		}
	}
}

int	check_opt_files(t_shell *shell, int index)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (shell->exec[index]->opt_files[i])
	{
		if (!shell->exec[index]->opt_flags[i])
			fd = open(shell->exec[index]->opt_files[i], O_CREAT | \
			O_WRONLY | O_TRUNC, 0644);
		else
			fd = open(shell->exec[index]->opt_files[i], O_CREAT | \
			O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			printf("%s: couldn't open file.\n", \
			shell->exec[index]->opt_files[i]);
			shell->environ->exit = 1;
			return (0);
		}
		else
			ft_close(shell, &fd);
		i++;
	}
	return (1);
}

int	check_inp_files(t_shell *shell, int index)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (shell->exec[index]->inp_files[i])
	{
		if (!shell->exec[index]->inp_flags[i])
		{
			fd = open(shell->exec[index]->inp_files[i], O_RDONLY);
			if (fd == -1)
			{
				printf("%s: No such file or directory\n", \
				shell->exec[index]->inp_files[i]);
				shell->environ->exit = 1;
				return (0);
			}
			else
				ft_close(shell, &fd);
		}
		i++;
	}
	return (1);
}
