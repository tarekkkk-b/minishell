/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:57:27 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/16 18:20:47 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_file(t_noding *traveler, t_tokens actual_token)
{
	if (traveler->next && (traveler->next->type == ARG
			|| traveler->next->type == actual_token))
		traveler->next->type = actual_token;
	else if (traveler->next && traveler->next->type == SPACE)
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
		// else if (traveler->type == HERE_DOC)
		// 	assign_file(traveler, DELIMITER);
		traveler = traveler->next;
	}
}

char	*full_string(t_shell *shell, t_noding *traveler, t_noding *add_after)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = NULL;
	add_after = traveler;
	while (traveler && traveler->type != SPACE && !operater_tokens(traveler))
	{
		temp = ft_strjoin(str, traveler->value);
		if (str)
			free(str);
		str = ft_strdup(temp);
		if (temp)
			free(temp);
		traveler->pop_out = 1;
		traveler = traveler->next;
		if (traveler && traveler->next && traveler->next->type != SPACE
			&& !operater_tokens(traveler->next))
			add_after = add_after->next;
	}
	return (str);
}

void	new_delim(t_shell *shell, t_noding *traveler, t_noding *pre, char *str)
{
	t_noding	*new;

	new = malloc(sizeof(t_noding));
	if (!new)
		return ;
	assign_node(shell, new, DELIMITER, 0);
	if (traveler)
		new->next = traveler->next;
	else
		new->next = NULL;
	pre->next = new;
	new->value = ft_strdup(str);
	free(str);
}

void	get_delimeter(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*temp;
	t_noding	*add_after;
	char		*str;

	traveler = shell->parser->noding;
	add_after = NULL;
	while (traveler && traveler->next)
	{
		if (traveler->type == HERE_DOC)
		{
			temp = traveler;
			if (traveler->next && traveler->next->type == SPACE)
				traveler = traveler->next;
			traveler = traveler->next;
			str = full_string(shell, traveler, add_after);
			if (str)
				new_delim(shell, traveler, add_after, str);
			else
				temp->type = INVALID;
		}
		if (traveler && traveler->next)
			traveler = traveler->next;
	}
}
