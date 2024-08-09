/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:51:43 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/09 22:40:11 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_echo(t_shell *shell, int index, int i)
{
	int	flag;
	int	j;

	flag = 0;
	while (shell->exec[index]->cmd[i] && shell->exec[index]->cmd[i][0] == '-' &&
		shell->exec[index]->cmd[i][1] == 'n')
	{
		j = 2;
		while (shell->exec[index]->cmd[i][j] == 'n')
			j++;
		if (shell->exec[index]->cmd[i][j] != '\0')
			break ;
		flag = 1;
		i++;
	}
	while (shell->exec[index]->cmd[i])
	{
		ft_putstr_fd(shell->exec[index]->cmd[i], 1);
		if (shell->exec[index]->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
