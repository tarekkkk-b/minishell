/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:47:06 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/16 13:21:16 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	operater_tokens(t_noding *node)
{
	if (!node)
		return (0);
	if (node->type == INVALID || node->type == PIPES
		|| node->type == INP_REDIR || node->type == OPT_REDIR
		|| node->type == HERE_DOC || node->type == APPEND)
		return (1);
	return (0);
}

int	delimeter_char(char character)
{
	if (character == '>' || character == '<' || character == ' '
		|| character == '\t' || character == '\'' || character == '"'
		|| character == '|' || character == '\0' || character == ';'
		|| character == '\\' || character == ')' || character == '('
		|| character == '$' || character == '&' || character == '*')
		return (1);
	return (0);
}

int	invalid_chars(char c)
{
	if (c == '&' || c == ';' || c == '\\' || c == '*' || c == '(' || c == ')')
		return (1);
	return (0);
}

int	invalid_token(t_shell *shell)
{
	t_noding	*last_token;

	if (!shell->parser->noding || !last_node(shell->parser->noding))
		return (0);
	last_token = last_node(shell->parser->noding);
	if (operater_tokens(last_token))
		return (1);
	else if (last_token->type == SPACE)
		if (!prev_node(shell, last_token)
			|| operater_tokens(prev_node(shell, last_token)))
			return (1);
	return (0);
}
