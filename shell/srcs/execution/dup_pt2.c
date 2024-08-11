/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:51:34 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:52:17 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		ft_close(exec->shell, &fd);
		return (1);
	}
	return (0);
}
