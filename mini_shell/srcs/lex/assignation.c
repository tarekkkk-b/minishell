/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:15:53 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/15 21:53:49 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	assign_pipe(t_shell *shell)
// {
// 	t_noding *new;
	
// 	new = malloc(sizeof(t_noding));
// 	new->value = ft_strdup("|");
// 	if (invalid_token(shell) || !shell->parser->noding
// 	|| last_node(shell->parser->noding)->type == PIPES
// 	|| (last_node(shell->parser->noding)->type == SPACE
// 	&& prev_node(shell, last_node(shell->parser->noding))->type == PIPES))
// 		assign_node(shell, new, INVALID, 0);
// 	else
// 		assign_node(shell, new, PIPES, 0);
// 	token_node(shell, new);
// }

int	assign_space(char *str, int index, t_shell *shell)
{
	t_noding	*new;

	while ((str[index] == ' ' || str[index] == '\t') && str[index] != '\0')
		index++;
	index--;
	new = malloc(sizeof(t_noding));
	if (!new)
		return (-1);
	assign_node(shell, new, SPACE, 1);
	new->value = ft_strdup(" ");
	token_node(shell, new);
	return (index);
}

void	assign_invalid(t_shell *shell, char *str, int index)
{
	t_noding *new;
	
	new = malloc(sizeof(t_noding));
	if (!new)
		return ;
	assign_node(shell, new, INVALID, 0);
	new->value = malloc(sizeof(char) * 2);
	if (!new->value)
		return (free(new));
	new->value[0] = str[index];
	new->value[1] = '\0';
	token_node(shell, new);
}

int	assign_word(char *str, int index, t_shell *shell)
{
	t_noding	*new;
	int			temp;
	int			j;

	j = 0;
	temp = index;
	new = malloc(sizeof(t_noding));
	if (!new)
		return (-1);
	assign_node(shell, new, ARG, 0);
	while (!delimeter_char(str[index + 1]))
		index++;
	new->value = malloc(sizeof(char) * (index - temp + 2));
	if (!new->value)
		return (free(new), -1);
	while (temp <= index)
		new->value[j++] = str[temp++];
	new->value[j] = '\0';
	token_node(shell, new);
	return (index);
}
