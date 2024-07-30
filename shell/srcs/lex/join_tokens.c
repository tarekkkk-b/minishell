/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:31:17 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/22 15:47:55 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*loop(t_noding **traveler, t_noding **add_after)
{
	char	*str;

	str = NULL;
	while ((*traveler) && (*traveler)->type != SPACES
		&& !operater_tokens((*traveler)) && (*traveler)->type != PIPES)
	{
		(*add_after) = (*traveler);
		if (!(*traveler)->pop_out)
			str = ft_strjoin(str, (*traveler)->value, 1);
		(*traveler)->pop_out = 1;
		(*traveler) = (*traveler)->next;
	}
	return (str);
}

void	new_token(t_shell *shell, t_noding **traveler,
				t_noding **pre, char *str)
{
	t_noding	*new;

	(void)traveler;
	new = ft_malloc(sizeof(t_noding), shell);
	assign_node(shell, new, ARG, 0);
	if ((*pre))
		new->next = (*pre)->next;
	else
		new->next = NULL;
	(*pre)->next = new;
	new->value = ft_strdup(str);
	if (str)
		ft_free((void **)&str);
}

void	join_tokens(t_shell *shell)
{
	t_noding	*traveler;
	t_noding	*add_after;
	char		*str;

	traveler = shell->parser->noding;
	add_after = NULL;
	while (traveler)
	{
		str = loop(&traveler, &add_after);
		if (str)
			new_token(shell, &traveler, &add_after, str);
		if (traveler)
			traveler = traveler->next;
	}
}
