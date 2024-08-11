/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:08:39 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 11:54:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_exit(t_shell *shell, int argc, int index)
{
	int	exit_code;

	exit_code = 0;
	if (argc >= 2 && (is_num(shell->exec[index]->cmd[1]) == 1))
	{
		printf("exit: %s: numeric argument required\n", \
		shell->exec[index]->cmd[1]);
		exit_code = 255;
	}
	else if (argc == 2)
		exit_code = ft_atoi(shell->exec[index]->cmd[1]);
	else if (argc > 2)
	{
		write(1, "exit\n", 5);
		write(1, "exit: too many arguments\n", 25);
		return (1);
	}
	write(1, "exit\n", 5);
	mass_free(shell, exit_code);
	return (exit_code);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[0])
		return (1);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!str[i])
		return (0);
	return (1);
}
