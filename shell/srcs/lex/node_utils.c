/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:55:19 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/07 12:39:03 by tabadawi         ###   ########.fr       */
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

void	add_token(t_shell *shell, t_noding *new)
{
	t_noding	*temp;

	if (shell->parser->noding)
	{
		temp = last_node(shell->parser->noding);
		// printf("%s\n", temp->value);
		temp->next = new;
	}
	else
		shell->parser->noding = new;
}

void	popout_token(t_shell *shell, t_noding *token)
{
	t_noding	*temp;
	t_noding	*bye;

	if (!shell || !token)
		return ;
	temp = shell->parser->noding;
	if (token == shell->parser->noding)
	{
		shell->parser->noding = shell->parser->noding->next;
		return (ft_free((void **)&temp->value), ft_free((void **)&temp));
	}
	bye = token;
	while (temp && temp->next && temp->next != bye)
		temp = temp->next;
	temp->next = bye->next;
	return (ft_free((void **)&bye->value), ft_free((void **)&bye));
}

t_noding	*prev_node(t_shell *shell, t_noding *target)
{
	t_noding	*traveler;

	traveler = NULL;
	if (!shell->parser->noding || !target)
		return (NULL);
	if (shell->parser->noding)
	{
		traveler = shell->parser->noding;
		while (traveler && traveler->next && traveler->next != target)
			traveler = traveler->next;
	}
	return (traveler);
}

t_noding	*last_node(t_noding *nodes)
{
	if (!nodes)
		return (NULL);
	while (nodes)
	{
		if (!nodes->next)
			return (nodes);
		nodes = nodes->next;
	}
	return (nodes);
}
