/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/21 11:40:17 by ahaarij          ###   ########.fr       */
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


void	*ft_malloc(size_t size)
{
	void	*ptr;
	ptr = malloc(size);
	if(!ptr)
		return (NULL);
		// major fweeing function in place of return null, that takes an exit code
	else
		return(ptr);
}

void	ft_free(void **ptr)
{
	if(ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}

// fake int main
// {
// 	int* a = (int*)ft_malloc(sizeof(int) * 10);
//	a = {0};
// 	ft_free((void**)&a);
// }