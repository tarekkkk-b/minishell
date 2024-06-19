/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:22:40 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/19 19:48:48 by tabadawi         ###   ########.fr       */
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

void	change_node(t_values *node, char *new)
{
	free(node->string);
	node->value = ft_strdup(new);
	node->string = ft_strjoin2(node->key, "=", node->value);
}

t_values	*locate_node(t_values *temp, char *target_key)
{
	t_values	*travel;
	if (temp)
	{
		travel = temp;
		while (travel)
		{
			if (!ft_strncmp(target_key, travel->key, ft_strlen(travel->key)))
				return (travel);
			travel = travel->next;
		}
	}
	return (NULL);
}

void	adjust_lvl(t_values *env_node, t_shell *shell)
{
	t_values *temp;

	temp = locate_node(env_node, "SHLVL");
	if (!temp)
		return ;	//create SHLVL=1
	int tempp = ft_atoi(temp->value);
	shell->environ->shlvl = tempp + 1;
	char *str = ft_itoa(shell->environ->shlvl);
	change_node(temp, str);
	free(str);	
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
	adjust_lvl(shell->environ->env, shell);
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
