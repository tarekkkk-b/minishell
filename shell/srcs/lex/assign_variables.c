/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:50 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/09 16:55:41 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_name(char character, int current, int first)
{
	if (current == first)
	{
		if (character == '?')
			return (1);
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

void	add_question(t_shell *shell, t_noding *new)
{
	assign_node(shell, new, VARIABLE, 0);
	new->value = ft_strdup("?");
	add_token(shell, new);
}

int	assign_variable(char *str, int i, t_shell *shell)
{
	t_noding	*new;
	int			temp;
	int			j;

	j = 0;
	new = ft_malloc(sizeof(t_noding), shell);
	if (str[i + 1] == '?')
		return (add_question(shell, new), i + 1);
	else if (str[i + 1] == ' ' || str[i + 1] == '\t' || str[i + 1] == '\0'
		|| !valid_name(str[i + 1], i + 1, i + 1))
		assign_node(shell, new, ARG, 0);
	else
		assign_node(shell, new, VARIABLE, 0);
	temp = i;
	i = end_of_var(str, temp + 1, i, 2);
	new->value = ft_malloc(sizeof(char) * (i - temp + 3), shell);
	new->value[j++] = '$';
	while (temp++ < i)
		new->value[j++] = str[temp];
	new->value[j++] = '\0';
	add_token(shell, new);
	return (i);
}
