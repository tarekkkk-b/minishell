/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   popout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:28:04 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/22 09:29:05 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	popout(t_shell	*shell, char *target)
{
	t_values	*tnode;
	t_values	*temp1;

	temp1 = shell->environ->env;
	tnode = locate_node(shell->environ->env, target);
	if (!tnode)
		return ;
	if (tnode == shell->environ->env)
		shell->environ->env = shell->environ->env->next;
	else
	{
		temp1 = shell->environ->env;
		while (temp1->next != tnode)
			temp1 = temp1->next;
		temp1->next = tnode->next;
	}
	ft_free((void **)&tnode->key);
	ft_free((void **)&tnode->value);
	ft_free((void **)&tnode->string);
	free (tnode);
}
