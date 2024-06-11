/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/11 11:55:23 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)av;
	(void)env;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	char *path;
	char *accpath;
	char *str;
	while (1)
	{
		path = getcwd(NULL, 0);
		accpath = ft_strjoin(path, "> ");
		str = readline(accpath);
		if (str[0] != '\0')
			add_history(str);
		free (str);
	}
}
