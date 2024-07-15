/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:24 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/15 21:38:08 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	single_red(t_shell *shell, t_noding *new, char *str, int index)
{
	if (str[index] == '>')
	{
		if (!invalid_token(shell))
			new->type = APPEND;
		else
			new->type = INVALID;
		new->value = ft_strdup(">>");
	}
	else if (str[index] == '<')
	{
		if (!invalid_token(shell))
			new->type = HERE_DOC;
		else
			new->type = INVALID;
		new->value = ft_strdup("<<");
	}
}

static void	double_red(t_shell *shell, t_noding *new, char *str, int index)
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
	t_noding *new;
	new = malloc(sizeof(t_noding));
	if (str[index + 1] == str[index])
	{
		single_red(shell, new, str, index);
		index++;
	}
	else if (str[index + 1] != str[index])
		double_red(shell, new, str, index);
	token_node(shell, new);
	return (index);
}
