/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:15:53 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/06 18:06:56 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_pipe(t_shell *shell)
{
	t_noding	*new;
	t_noding	*last_token;

	last_token = last_node(shell->parser->noding);
	new = ft_malloc(sizeof(t_noding), shell);
	new->value = ft_strdup("|");
	if (invalid_token(shell) || !shell->parser->noding
		|| last_token->type == PIPES || (last_token->type == SPACES
			&& prev_node(shell, last_token)->type == PIPES))
		assign_node(shell, new, INVALID, 0);
	else
	{
		assign_node(shell, new, PIPES, 0);
		shell->parser->pipe_count++;
	}
	add_token(shell, new);
}

int	assign_space(char *str, int index, t_shell *shell)
{
	t_noding	*new;

	while ((str[index] == ' ' || str[index] == '\t') && str[index] != '\0')
		index++;
	index--;
	new = ft_malloc(sizeof(t_noding), shell);
	if (!new)
		return (-1);
	assign_node(shell, new, SPACES, 1);
	new->value = ft_strdup(" ");
	add_token(shell, new);
	return (index);
}

void	assign_invalid(t_shell *shell, char *str, int index)
{
	t_noding	*new;

	new = ft_malloc(sizeof(t_noding), shell);
	if (!new)
		return ;
	assign_node(shell, new, INVALID, 0);
	new->value = ft_malloc((sizeof(char) * 2), shell);
	if (!new->value)
		return (ft_free((void **)&new));
	new->value[0] = str[index];
	new->value[1] = '\0';
	add_token(shell, new);
}

int	assign_word(char *str, int index, t_shell *shell)
{
	t_noding	*new;
	int			temp;
	int			j;

	j = 0;
	temp = index;
	new = ft_malloc(sizeof(t_noding), shell);
	if (!new)
		return (-1);
	assign_node(shell, new, ARG, 0);
	while (!delimeter_char(str[index + 1]))
		index++;
	new->value = ft_malloc(sizeof(char) * (index - temp + 2), shell);
	if (!new->value)
		return (ft_free((void **)&new), -1);
	while (temp <= index)
		new->value[j++] = str[temp++];
	new->value[j] = '\0';
	add_token(shell, new);
	return (index);
}
