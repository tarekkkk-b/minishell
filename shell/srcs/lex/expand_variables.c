/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:49:59 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/09 14:20:39 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	question(t_shell *shell, t_noding *traveler)
{
	traveler->type = ARG;
	ft_free((void **)&traveler->value);
	traveler->value = ft_itoa(shell->environ->exit);
}

void	get_var(t_shell *shell, t_noding *traveler)
{
	t_values	*env_traveler;
	char		*str;
	int			t;
	int			o;

	t = 1;
	o = 0;
	if (traveler->value[0] == '?')
		return (question(shell, traveler));
	str = ft_malloc(sizeof(char) * (ft_strlen(traveler->value)), shell);
	while (traveler->value[t])
		str[o++] = traveler->value[t++];
	str[o++] = '\0';
	env_traveler = locate_node(shell->environ->env, str);
	ft_free((void **)&str);
	if (!env_traveler)
		traveler->pop_out = 1;
	else
	{
		ft_free((void **)&traveler->value);
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
