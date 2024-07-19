/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:49:59 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/17 13:29:00 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_var(t_shell *shell, t_noding *traveler)
{
	t_values	*env_traveler;

	env_traveler = locate_node(shell->environ->env, traveler->value);
	if (!env_traveler)
		traveler->pop_out = 1;
	else
	{
		free(traveler->value);
		traveler->value = ft_strdup(env_traveler->value);
		traveler->type = ARG;
	}
}

void	expand_vars(t_shell *shell)
{
	t_noding	*traveler;

	traveler = shell->parser->noding;
	while (traveler)
	{
		if (traveler->type == VARIABLE)
			get_var(shell, traveler);
		traveler = traveler->next;
	}
}
