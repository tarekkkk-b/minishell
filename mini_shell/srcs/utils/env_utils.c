/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:22:40 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/18 21:42:38 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	assign_nodes(char **env, t_shell *shell, t_values *node, int i)
{
	node->key = get_key(env[i]);
	node->value = getenv(node->key);
	node->string = ft_strjoin2(node->key, "=", node->value);
	node->shell = shell;
	node->next = NULL;
}

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
		assign_nodes(env, shell, node, i);
		addnode(shell->environ, node);
	}
}

char	**arr(t_values *environ)
{
	char		**env;
	t_values	*temp;
	int i = 0;
	if (!environ)
		return (NULL);
	temp = environ;
	while (temp)
	{
		if (!temp->next)
		{
			i++;
			break ;
		}
		temp = temp->next;
		i++;
	}
	env = malloc(sizeof(char *) * (i + 1));
	temp = environ;
	i = 0;
	while (temp)
	{
		env[i] = ft_strdup(temp->string);
		if (!temp->next)
			break ;
		temp = temp->next;
		i++;
	}
	env[++i] = NULL;
	return(env);
}

