/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:57:44 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/16 17:24:10 by tabadawi         ###   ########.fr       */
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

void	assignation(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	shell->parser = malloc(sizeof(t_parser));
	shell->parser->noding = NULL;
	while (str[i++])
	{
		if (str[i] == '|')
			assign_pipe(shell);
		else if (str[i] == '>' || str[i] == '<')
			i = assign_redirection(str, i, shell);
		else if (str[i] == ' ' | str[i] == '\t')
			i = assign_space(str, i, shell);
		else if (str[i] == '$')
			i = assign_variable(str, i, shell);
		else if (str[i] == '"' || str[i] == '\'')
			i = assign_quotes(str, i, shell);
		else if (invalid_chars(str[i]) == 1)
			assign_invalid(shell, str, i);
		else
			i = assign_word(str, i, shell);
	}
}

void	parsing_hub(t_shell *shell, char *str)
{
	assignation(shell, str);
	get_delimeter(shell);
	quotes(shell);
	expand_vars(shell);
	join_tokens(shell);
	test_pop_out(shell);
	assign_files(shell);
	t_noding	*test;
	test = shell->parser->noding;
	while (test)
	{
		printf("%s		:		%s	pop? <<%d>>\n",
		test->value, types[test->type], test->pop_out);
		test = test->next;
	}
}
