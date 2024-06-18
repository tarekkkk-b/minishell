/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/18 17:22:11 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_arrlen(char **arr)
{
	int i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

char	*get_key(char *env_var)
{
	int i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	char *key = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (env_var[i] && env_var[i] != '=')
	{
		key[i] = env_var[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_values	*lstlast(t_values *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	addnode(t_environ *environ, t_values *node)
{
	t_values	*temp;

	if (environ->env)
	{
		temp = lstlast(environ->env);
		temp->next = node;
	}
	else
		environ->env = node;
}

void	create_env(char **env, t_shell *shell)
{
	int i = -1;
	t_values	*node;
	int	len = get_arrlen(env);
	shell->environ = malloc(sizeof(t_environ));
	shell->environ->env = NULL;
	shell->environ->owd = getcwd(NULL, 0);
	shell->environ->cwd = getcwd(NULL, 0);
	shell->environ->exit = 0;
	while (++i < len)
	{
		node = malloc(sizeof(t_values));
		node->name = get_key(env[i]);
		node->value = getenv(node->name);
		node->string = ft_strjoin(ft_strjoin(node->name, "="), node->value);
		node->shell = shell;
		node->next = NULL;
		addnode(shell->environ, node);
	}
}

int	main(int ac, char **av, char **env)
{
	char 		*path;
	char 		*str;
	t_shell		shell;
	(void)av;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	while (1)
	{
		path = ft_strjoin(shell.environ->cwd, "> ");
		str = readline(path);
		if (str[0] != '\0')
			add_history(str);
		free (str);
	}
}
