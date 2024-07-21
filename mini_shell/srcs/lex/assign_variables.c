/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:50 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/21 21:09:44 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char character, int current, int first)
{
	if (current == first)
	{
		if ((character >= '0' && character <= '9') || (character == '$'))
			return (2);
		if (!(character >= 'a' && character <= 'z')
			&& !(character >= 'A' && character <= 'Z') && character != '_')
			return (0);
	}
	else
	{
		if (!(character >= 'a' && character <= 'z')
			&& !(character >= 'A' && character <= 'Z') && character != '_'
			&& !(character >= '0' && character <= '9'))
			return (0);
	}
	return (1);
}

int	end_of_var(char *str, int start, int index, int res)
{
	while (str[index + 1] && valid_name(str[index + 1], index + 1, start))
	{
		if (valid_name(str[index + 1], index + 1, start) == res)
		{
			index++;
			break ;
		}
		index++;
	}
	return (index);
}

int	assign_variable(char *str, int index, t_shell *shell)
{
	t_noding	*new;
	int			temp;
	int			j;

	j = 0;
	new = ft_malloc(sizeof(t_noding));
	if (!new)
		return (-1);
	if (str[index + 1] == ' ' || str[index + 1] == '\t'
		|| str[index + 1] == '\0'
		|| !valid_name(str[index + 1], index + 1, index + 1))
		assign_node(shell, new, ARG, 0);
	else
		assign_node(shell, new, VARIABLE, 0);
	temp = index;
	index = end_of_var(str, temp + 1, index, 2);
	new->value = ft_malloc(sizeof(char) * (index - temp + 3));
	if (!new->value)
		return (ft_free((void **)&new), -1);
	new->value[j++] = '$';
	while (temp++ < index)
		new->value[j++] = str[temp];
	new->value[j++] = '\0';
	add_token(shell, new);
	return (index);
}
