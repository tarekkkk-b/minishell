/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:57:44 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/21 14:15:41 by tabadawi         ###   ########.fr       */
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

// dis is now in temp_file ^^^

void	pop_extras(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*temp;

	traveler = shell->parser->noding;
	while (traveler)
	{
		if (traveler->pop_out)
		{
			temp = traveler;
			traveler = traveler->next;
			popout_token(shell, temp);
		}
		if (traveler && !traveler->pop_out)
			traveler = traveler->next;
	}
}

void	assignation(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	shell->parser = ft_malloc(sizeof(t_parser));
	shell->parser->noding = NULL;
	while (str[i])
	{
		if (str[i] == '|')
			assign_pipe(shell);
		else if (str[i] == '>' || str[i] == '<')
			i = assign_redirection(str, i, shell);
		else if (str[i] == ' ' || str[i] == '\t')
			i = assign_space(str, i, shell);
		else if (str[i] == '$')
			i = assign_variable(str, i, shell);
		else if (str[i] == '"' || str[i] == '\'')
			i = assign_quotes(str, i, shell);
		else if (invalid_chars(str[i]) == 1)
			assign_invalid(shell, str, i); 
		else
			i = assign_word(str, i, shell);
		i++;
	}
}

int	parsing_hub(t_shell *shell, char *str)
{
	assignation(shell, str);
	get_delimeter(shell);
	quotes(shell);
	expand_vars(shell);
	join_tokens(shell);
	pop_extras(shell);
	assign_files(shell);
	return (checker(shell));
}
