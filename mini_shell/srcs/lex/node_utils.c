/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:55:19 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/15 18:01:04 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_node(t_shell *shell, t_noding *new, t_tokens type, int popout)
{
	new->next = NULL;
	new->shell = shell;
	new->pop_out = popout;
	new->type = type;
}
