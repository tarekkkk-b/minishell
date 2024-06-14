/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/14 21:36:33 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_env
{
	int		exit;
	int		shlvl;
	char	*cwd;
	char	*owd;
	char	**env;
	char	**path;
}	t_env;

typedef	struct s_shell
{
	t_env	*env;
}	t_shell;



int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	shell.env = malloc(sizeof(t_env));
	(void)av;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");

	char *test = getenv("SHLVL");
	printf("%s\n\n", test);


	
	while (1)
	{
		// path = getcwd(NULL, 0);
		// accpath = ft_strjoin(path, "> ");
		// str = readline(accpath);
		// if (str[0] != '\0')
		// 	add_history(str);
		// free (str);
	}
}
