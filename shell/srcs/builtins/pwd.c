/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:05:21 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/06 13:33:11 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_pwd(t_shell *shell)
{
	char	str[PATH_MAX];

	(void) shell;
	if (getcwd(str, 1024))
	{
		ft_putendl_fd(str, 1);
		return (0);
	}
	else
		return (1);
}
