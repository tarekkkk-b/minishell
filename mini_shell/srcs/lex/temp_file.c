/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/19 23:41:27 by ahaarij          ###   ########.fr       */
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
	[SPACE] = "SPACE",
	[VARIABLE] = "VARIABLE",
	[DQUOTES] = "QUOTES",
	[INVALID] = "INVALID"
};

// just copied dis over ^^


void    checker(t_shell *shell)
{
    t_noding *last = last_node(shell->parser->noding);
    if (last)
    {
        if (last->type == PIPES)
        {
            last->type = INVALID;
        }
    }
    t_noding *temp;
    temp = shell->parser->noding;
    while (temp)
	{
		printf("%s		:		%s	pop? <<%d>>\n",
		temp->value, types[temp->type], temp->pop_out);
        if(temp->type == INVALID)
            printf("Syntax error at:                '%s'\n", temp->value);
		temp = temp->next;
	}
}