/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:57:27 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/22 15:48:07 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_file(t_noding *traveler, t_tokens actual_token)
{
	if (traveler->next && (traveler->next->type == ARG
			|| traveler->next->type == actual_token))
		traveler->next->type = actual_token;
	else if (traveler->next && traveler->next->type == SPACES)
	{
		if (traveler->next->next && (traveler->next->next->type == ARG
				|| traveler->next->next->type == actual_token))
			traveler->next->next->type = actual_token;
		else
			traveler->type = INVALID;
	}
	else
		traveler->type = INVALID;
}

void	assign_files(t_shell *shell)
{
	t_noding	*traveler;

	if (!shell->parser || !shell->parser->noding)
		return ;
	traveler = shell->parser->noding;
	while (traveler)
	{
		if (traveler->type == INP_REDIR)
			assign_file(traveler, INP_FILE);
		else if (traveler->type == OPT_REDIR || traveler->type == APPEND)
			assign_file(traveler, OPT_FILE);
		else if (traveler->type == HERE_DOC)
			assign_file(traveler, DELIMITER);
		traveler = traveler->next;
	}
}

char	*full_string(t_noding *traveler)
{
	char	*str;

	str = NULL;
	while (traveler && traveler->type != SPACES && !operater_tokens(traveler))
	{
		str = ft_strjoin(str, traveler->value, 1);
		traveler->pop_out = 1;
		traveler = traveler->next;
	}
	return (str);
}

void	new_delim(t_shell *shell, t_noding *traveler, t_noding *pre, char *str)
{
	t_noding	*new;

	new = ft_malloc(sizeof(t_noding), shell);
	if (!new)
		return ;
	assign_node(shell, new, DELIMITER, 0);
	if (traveler)
		new->next = traveler->next;
	else
		new->next = NULL;
	pre->next = new;
	new->value = ft_strdup(str);
	ft_free((void **)&str);
}

void	get_delimeter(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*temp;
	char		*str;

	traveler = shell->parser->noding;
	while (traveler && traveler->next)
	{
		if (traveler->type == HERE_DOC)
		{
			temp = traveler;
			if (traveler->next && traveler->next->type == SPACES)
				traveler = traveler->next;
			traveler = traveler->next;
			str = full_string(traveler);
			if (str && temp->next && temp->next->type == SPACES)
				new_delim(shell, traveler, temp->next, str);
			else if (str && !(temp->next && temp->next->type == SPACES))
				new_delim(shell, traveler, temp, str);
			else
				temp->type = INVALID;
		}
		if (traveler && traveler->next)
			traveler = traveler->next;
	}
}