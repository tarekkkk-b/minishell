/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:31:17 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/20 17:50:21 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *loop(t_noding **traveler, t_noding **add_after)
{
	char	*str;

	str = NULL;
	while ((*traveler) && (*traveler)->type != SPACES
			&& !operater_tokens((*traveler)) && (*traveler)->type != PIPES)
	{
		(*add_after) = (*traveler);
		if (!(*traveler)->pop_out)
			str = ft_strjoin(str, (*traveler)->value);
		(*traveler)->pop_out = 1;
		(*traveler) = (*traveler)->next;
	}
	return (str);
}

void	new_token(t_shell *shell, t_noding **traveler, t_noding **pre, char *str)
{
	t_noding	*new;

	(void)traveler;
	new = malloc(sizeof(t_noding));
	assign_node(shell, new, ARG, 0);
	if ((*pre))
		new->next = (*pre)->next;
	else
		new->next = NULL;
	(*pre)->next = new;
	new->value = ft_strdup(str);
	if (str)
		free(str);
}

void	 join_tokens(t_shell *shell)
{
	t_noding	*traveler = shell->parser->noding;
	t_noding	*add_after = NULL;
	char		*str;

	while (traveler)
	{
		str = loop(&traveler, &add_after);
		if (str)
			new_token(shell, &traveler, &add_after, str);
		if (traveler)
			traveler = traveler->next;
	}
}
