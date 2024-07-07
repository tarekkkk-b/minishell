/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:05:21 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/07 14:16:33 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_shell *shell)
{
	(void)shell;
	// int i = 0;
	// 1024 max lengt it should be
	char str[PATH_MAX];
	if(getcwd(str, 1024))
	{
		ft_putendl_fd(str, 0);
		return (0);
	}
	else
		return (1);
}