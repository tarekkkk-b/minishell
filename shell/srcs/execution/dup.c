/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:50:58 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/11 12:58:39 by ahaarij          ###   ########.fr       */
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

int	check_opt_files(t_shell *shell, int index)
{
	int	i;
	int	fd;

	fd = -1;
	i = 0;
	while (shell->exec[index]->opt_files[i])
	{
		if (shell->exec[index]->opt_flags[i] == 0)
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
