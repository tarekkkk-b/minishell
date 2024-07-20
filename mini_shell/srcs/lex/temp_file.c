/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/20 22:01:25 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static const char * const types[] = {
	[COMMAND] = "CMD",
	[ARG] = "ARG",
	[PIPES] = "PIPE",
	[INP_REDIR] = "INP_REDIR",
	[INP_FILE] = "INP_FILE",
	[OPT_REDIR] = "OPT_REDIR",
	[OPT_FILE] = "OPT_FILE",
	[HERE_DOC] = "HEREDOC",
	[DELIMITER] = "DELIMITER",
	[APPEND] = "APPEND",
	[SPACES] = "SPACES",
	[VARIABLE] = "VARIABLE",
	[DQUOTES] = "QUOTES",
	[INVALID] = "INVALID"
};

// just copied dis over ^^


int    checker(t_shell *shell)
{
    t_noding	*last;
	t_noding	*temp;
	
	last = last_node(shell->parser->noding);
    if (last)
        if (last->type == PIPES)
            last->type = INVALID;
    temp = shell->parser->noding;
    while (temp)
	{
		printf("%s		:		%s	<<<pop? == %d>>>\n", temp->value, types[temp->type], temp->pop_out);
        if(temp->type == INVALID)
		{
        	return ((void)printf("Syntax error at:	'%s'\n", temp->value), 0);
		}
		temp = temp->next;
	}
	return (1);
}
