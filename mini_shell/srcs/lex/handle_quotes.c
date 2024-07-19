/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 21:09:10 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/07/19 20:09:11 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_qoutes(t_noding *suspect)
{
	int i = 0;
	while (suspect->value[i])
	{
		if (suspect->value[i] == '$')
			if (suspect->value[i + 1]
				&& valid_name(suspect->value[i + 1], i + 1, i + 1))
				return (1);	
		i++;
	}
	return (0);
}

int	new_word(t_shell *shell, t_noding *suspect, t_noding **add_after, int i)
{
	t_noding	*new;
	int			copier;

	new = malloc(sizeof(t_noding));
	if (!new)
		return (-1);
	assign_node(shell, new, ARG, 0);
	new->next = (*add_after)->next;
	copier = i;
	while (suspect->value[i])
	{	
		if (suspect->value[i + 1] == '$')
		{
			if (valid_name(suspect->value[i + 2], i + 2, i + 1))
			{				
				i++;
				break ;
			}
		}
		i++;
	}
	new->value = malloc(sizeof(char) * (i - copier + 1));
	int j = 0;
	while (copier < i)
		new->value[j++] = suspect->value[copier++];
	new->value[j++] = '\0';
	(*add_after)->next = new;
	(*add_after) = (*add_after)->next;
	return (i);
}

int	new_var(t_shell *shell, t_noding *suspect, t_noding **add_after, int i)
{
	t_noding	*new;
	int			reset;
	int			copier;

	new = malloc(sizeof(t_noding));
	assign_node(shell, new, VARIABLE, 0);
	new->next = (*add_after)->next;
	reset = i;
	if (suspect->value[i + 1])
		i++;
	copier = 0;
	i = end_of_var(suspect->value, i, reset, 2);
	new->value = malloc(sizeof(char) * (i - reset + 2));
	while (reset <= i)
		new->value[copier++] = suspect->value[reset++];
	new->value[copier] = '\0';
	(*add_after)->next = new;
	(*add_after) = (*add_after)->next;
	return (i);
}

t_noding	*divide_qoutes(t_shell *shell, t_noding *suspect)
{
	t_noding	*add_after;
	int			i;

	i = 0;
	add_after = suspect;
	while (suspect->value[i])
	{
		if (suspect->value[i] != '$')
			i = new_word(shell, suspect, &add_after, i);
		if(suspect->value[i] == '$')
			i = new_var(shell, suspect, &add_after, i);
		if (suspect->value[i])
			i++;
	}
	return (add_after);
}

void	quotes(t_shell *shell)
{
	t_noding	*traveler;

	if (!shell || !shell->parser || !shell->parser->noding)
		return ;
	traveler = shell->parser->noding;
	while (traveler)
	{
		if (traveler->type == DQUOTES)
		{
			if (check_qoutes(traveler))
			{
				traveler->pop_out = 1;
				traveler = divide_qoutes(shell, traveler);
				traveler = traveler->next;
			}
		}
		if (traveler)
			traveler = traveler->next;
		else
			break ;
	}
}
