/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/20 17:50:21 by tabadawi         ###   ########.fr       */
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
		printf("%s		:		%s\n",
		temp->value, types[temp->type]);
        if(temp->type == INVALID)
		{
            printf("Syntax error at:                '%s'\n", temp->value);	
			break ;
		}
		temp = temp->next;
	}
}