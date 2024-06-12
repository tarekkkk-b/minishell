/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/12 11:56:10 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	char *path;
	char *accpath;
	char *str;
	(void)av;
	(void)env;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
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
