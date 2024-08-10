/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:57 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/10 15:17:42 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_unset(t_shell *shell, int argc, int i)
{
	int			j;
	t_values	*mane;

	j = 1;
	while (argc > 1 && shell->exec[i]->cmd[j])
	{
		if (check_invalid(shell->exec[i]->cmd[j]) == 0)
		{
			mane = locate_node(shell->environ->env, shell->exec[i]->cmd[j]);
			if (mane != NULL)
				popout(shell, shell->exec[i]->cmd[j]);
			j++;
		}
		else
		{
			printf("%s : is not a valid identifier\n", shell->exec[i]->cmd[j]);
			return (1);
		}
	}
	return (0);
}
