/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:22:40 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/21 21:00:23 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	assign_nodes(char **env, t_shell *shell, t_values *node, int i)
// {
// 	node->key = get_key(env[i]);
// 	node->value = getenv(node->key);
// 	node->string = ft_strjoin2(node->key, "=", node->value);
// 	node->shell = shell;
// 	node->next = NULL;
// }

// dont need this ^^

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

void	adjust_lvl(t_shell *shell)
{
	t_values *temp;

	temp = locate_node(shell->environ->env, "SHLVL");
	if (!temp)
		return (custom_node(shell, "SHLVL", "1"));
		// return ;	//create SHLVL=1
	int tempp = ft_atoi(temp->value);
	shell->environ->shlvl = tempp + 1;
	char *str = ft_itoa(shell->environ->shlvl);
	change_node(temp, str);
	free(str);	
}

void	custom_node(t_shell *shell, char *key, char *value)
{
	if (!(!locate_node(shell->environ->env, key)))
		return ;
	t_values	*node;
	node = malloc(sizeof(t_values));
	node->index = 0;
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->string = ft_strjoin2(node->key, "=", node->value);
	node->shell = shell;
	node->next = NULL;
	addnode(shell->environ, node);
}

void	indexer(t_values *head)
{
	t_values	*traveler;
	int			i;

	i = 0;
	traveler = head;
	while (traveler)
	{
		traveler->index = i++;
		traveler = traveler->next;
	}
}

void	create_env(char **env, t_shell *shell)
{
	int i = -1;
	char	*str;
	shell->environ = malloc(sizeof(t_environ));
	shell->environ->env = NULL;
	shell->environ->owd = getcwd(NULL, 0);
	shell->environ->cwd = getcwd(NULL, 0);
	shell->environ->exit = 0;
	while (env[++i])
	{
		str = get_key(env[i]);
		custom_node(shell, str, getenv(str));
		free(str);
	}
	adjust_lvl(shell);
	indexer(shell->environ->env);
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

void	popout(t_shell	*shell, char *target)
{
	t_values	*tnode;
	t_values	*temp1 = shell->environ->env;
	// t_values	*temp2 = shell->environ->env;
	
	tnode = locate_node(shell->environ->env, target);
	if (!tnode)
		return ;
	if (tnode->index == 0)
		shell->environ->env = tnode->next;
	else
	{
		temp1 = shell->environ->env;
		while (temp1->index != tnode->index - 1)
			temp1 = temp1->next;
		temp1->next = tnode->next;
		// while (temp2->index != tnode->index + 1 && temp2->next != NULL)
		// 	temp2 = temp2->next;
		// if (!temp2)
		// 	temp1->next = temp2;
		// else
		// 	temp1->next = temp2->next;
	}
	free (tnode);
}

//POPPING PROTOTYPE

//if index == 0
	//shell->environ->env = node->next;
	//free (node);

//else if index != 0
	//while (temp->index != node->index - 1)
		//temp = temp->next;
	//while (temp2->index != node->index + 1 && temp2 != NULL)
		//temp2 = temp2->next;
	//temp->next = temp2;
	//free node;