/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:27:26 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/22 15:55:11 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	adjust_lvl(t_shell *shell)
{
	t_values	*temp;
	int			tempp;
	char		*str;

	temp = locate_node(shell->environ->env, "SHLVL");
	if (!temp)
		return (custom_node(shell, "SHLVL", "1"));
	tempp = ft_atoi(temp->value);
	shell->environ->shlvl = tempp + 1;
	str = ft_itoa(shell->environ->shlvl);
	change_node(temp, str);
	ft_free((void **)&str);
}

void	custom_node(t_shell *shell, char *key, char *value)
{
	t_values	*node;

	if (!(!locate_node(shell->environ->env, key)))
		return ;
	node = ft_malloc(sizeof(t_values), shell);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->string = ft_strjoin2(node->key, "=", node->value);
	node->shell = shell;
	node->next = NULL;
	addnode(shell->environ, node);
}

void	create_env(char **env, t_shell *shell)
{
	int		i;
	char	*str;

	i = -1;
	shell->environ = ft_malloc(sizeof(t_environ), shell);
	shell->environ->path = NULL;
	shell->environ->env = NULL;
	shell->environ->owd = getcwd(NULL, 0);
	shell->environ->cwd = ft_strdup(shell->environ->owd);
	shell->environ->exit = 0;
	while (env[++i])
	{
		str = get_key(env[i], shell);
		custom_node(shell, str, getenv(str));
		ft_free((void **)&str);
	}
	adjust_lvl(shell);
}

char	**arr(t_values *environ, t_shell *shell)
{
	char		**env;
	t_values	*temp;
	int			i;

	i = 0;
	if (!environ)
		return (NULL);
	temp = environ;
	i = ft_lstsizee(temp);
	i++;
	env = ft_malloc(sizeof(char *) * (i + 1), shell);
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
	return (env);
}
