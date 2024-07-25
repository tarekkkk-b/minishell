/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:57 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/25 14:25:14 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_unset(t_shell *shell, int argc, int i)
{
    int j = 1;
    t_values *mane;
    while(argc > 1 && shell->exec[i]->cmd[j])
    {
        if(check_invalid(shell->exec[i]->cmd[j]) == 0)
        {
            mane = locate_node(shell->environ->env, shell->exec[i]->cmd[j]);
			if(mane != NULL)
				popout(shell, shell->exec[i]->cmd[j]);
            j++;
        }
        else
        {
            printf("%s : is not a valid identifier\n", shell->exec[i]->cmd[j]);
            return(1);
        }
    }
    return(0);
}