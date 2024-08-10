/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:32:46 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/10 21:44:23 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_environ *environ)
{
	t_values	*current;

	if (environ == NULL)
	{
		printf("env : environ not set\n");
		return (1);
	}
	current = environ->env;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	return (0);
}
