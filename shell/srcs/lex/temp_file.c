/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 22:48:01 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/08 10:53:23 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static const char * const types[] = {
// 	[COMMAND] = "CMD",
// 	[ARG] = "ARG",
// 	[PIPES] = "PIPE",
// 	[INP_REDIR] = "INP_REDIR",
// 	[INP_FILE] = "INP_FILE",
// 	[OPT_REDIR] = "OPT_REDIR",
// 	[OPT_FILE] = "OPT_FILE",
// 	[HERE_DOC] = "HEREDOC",
// 	[DELIMITER] = "DELIMITER",
// 	[APPEND] = "APPEND",
// 	[SPACES] = "SPACES",
// 	[VARIABLE] = "VARIABLE",
// 	[DQUOTES] = "QUOTES",
// 	[INVALID] = "INVALID"
// };

// just copied dis over ^^

int	checker(t_shell *shell)
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
		if (temp->type == INVALID)
		{
			shell->environ->exit = 258;
			return ((void)printf("Syntax error at:	'%s'\n", temp->value), 0);
		}
		temp = temp->next;
	}
	return (1);
}

void	*ft_malloc(size_t size, t_shell *shell)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		return (ptr);
	mass_free(shell, 1);
	return (NULL);
}

void	ft_free(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
		return ;
	free(*ptr);
	*ptr = NULL;
}
