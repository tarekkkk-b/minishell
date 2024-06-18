/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_assignment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:31:34 by ahaarij           #+#    #+#             */
/*   Updated: 2024/06/18 17:40:38 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// dont judge me i had to pass int i lmao, also, change the file name if you want and the function names too, and also
// i havent tested the node->string strjoin function yet

void	assign_nodes(char **env, t_shell *shell, t_values *node, int i)
{
	
	node = malloc(sizeof(t_values));
	node->name = get_key(env[i]);
	node->value = getenv(node->name);
	node->string = ft_strjoin(ft_strjoin(node->name, "="), node->value);
	node->shell = shell;
	node->next = NULL;
}