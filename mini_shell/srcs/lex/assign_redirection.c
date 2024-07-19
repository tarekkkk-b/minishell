/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:24 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/18 16:29:24 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	double_red(t_shell *shell, t_noding *new, char *str, int index)
{
	if (str[index] == '>')
	{
		if (!invalid_token(shell))
			assign_node(shell, new, APPEND, 0);
		else
			assign_node(shell, new, INVALID, 0);
		new->value = ft_strdup(">>");
	}
	else if (str[index] == '<')
	{
		if (!invalid_token(shell))
			assign_node(shell, new, HERE_DOC, 0);
		else
			assign_node(shell, new, INVALID, 0);
		new->value = ft_strdup("<<");
	}
}

static void	single_red(t_shell *shell, t_noding *new, char *str, int index)
{
	if (str[index] == '>')
	{
		if (!invalid_token(shell))
			assign_node(shell, new, OPT_REDIR, 0);
		else
			assign_node(shell, new, INVALID, 0);
		new->value = ft_strdup(">");
	}
	else if (str[index] == '<')
	{
		if (!invalid_token(shell))
			assign_node(shell, new, INP_REDIR, 0);
		else
			assign_node(shell, new, INVALID, 0);
		new->value = ft_strdup("<");
	}
}

int	assign_redirection(char *str, int index, t_shell *shell)
{
	t_noding	*new;

	new = malloc(sizeof(t_noding));
	if (str[index + 1] == str[index])
	{
		double_red(shell, new, str, index);
		index++;
	}
	else if (str[index + 1] != str[index])
		single_red(shell, new, str, index);
	add_token(shell, new);
	return (index);
}
