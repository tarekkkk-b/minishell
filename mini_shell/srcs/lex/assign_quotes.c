/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:54:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/22 15:45:21 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	single_quotes(t_shell *shell, t_noding *new, char *str, int index)
{
	int	i;
	int	temp;
	int	counter;

	i = 0;
	temp = index;
	counter = 1;
	while (str[index + 1] && str[index + 1] != '\'' && str[index])
		index++;
	if (str[index + 1] == '\'')
	{
		temp++;
		index++;
		counter += 1;
	}
	new->value = ft_malloc(sizeof(char) * (index - temp + 1), shell);
	while (temp < index)
		new->value[i++] = str[temp++];
	new->value[i++] = '\0';
	if (counter != 2)
		assign_node(shell, new, INVALID, 0);
	else
		assign_node(shell, new, ARG, 0);
	return (index);
}

int	double_quotes(t_shell *shell, t_noding *new, char *str, int index)
{
	int	i;
	int	temp;
	int	counter;

	i = 0;
	temp = index;
	counter = 1;
	while (str[index + 1] && str[index + 1] != '"' && str[index])
		index++;
	if (str[index + 1] == '"')
	{
		temp++;
		index++;
		counter += 1;
	}
	new->value = ft_malloc(sizeof(char) * (index - temp + 1), shell);
	while (temp < index)
		new->value[i++] = str[temp++];
	new->value[i++] = '\0';
	if (counter != 2)
		assign_node(shell, new, INVALID, 0);
	else
		assign_node(shell, new, DQUOTES, 0);
	return (index);
}

int	assign_quotes(char *str, int index, t_shell *shell)
{
	t_noding	*new;

	new = ft_malloc(sizeof(t_noding), shell);
	if (!new)
		return (-1);
	if (str[index] == '"')
		index = double_quotes(shell, new, str, index);
	else if (str[index] == '\'')
		index = single_quotes(shell, new, str, index);
	add_token(shell, new);
	return (index);
}
