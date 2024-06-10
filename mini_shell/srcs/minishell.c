/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/10 21:48:21 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char *str)
{
	int i = 0;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	char *path = "minishell> ";
	char *str;
	while (1)
	{
		str = readline(path);
		if (!is_space(str))
			add_history(str);
		free (str);
	}
}