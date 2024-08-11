/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:51:23 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:49:39 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(t_shell *shell, int i, int args)
{
	char	*directory;
	char	*tempcwd;

	directory = get_directory(args, shell, i);
	if (directory == NULL)
		return (1);
	if (chdir(directory) == -1)
	{
		printf("cd: %s: No such file or directory\n", directory);
		return (1);
	}
	if (shell->exec[i]->cmd[i + 1] && \
	ft_strncmp(shell->exec[i]->cmd[i + 1], "-", 2) == 0)
		printf("%s\n", directory);
	tempcwd = getcwd(NULL, 0);
	if (!tempcwd)
	{
		printf("No such file or directory\n");
		return (0);
	}
	if (update_pwd(shell, tempcwd) == 1)
		return (ft_free((void **)&tempcwd), 1);
	return (free(tempcwd), 0);
}

char	*get_directory(int args_count, t_shell *shell, int i)
{
	char	*dir;

	dir = NULL;
	if (args_count == 1)
	{
		dir = find_node_aarij(shell->environ->env, "HOME");
		if (dir == NULL)
			printf("cd: HOME not set\n");
	}
	else if (shell->exec[i]->cmd[1] && \
	ft_strncmp(shell->exec[i]->cmd[1], "-", 2) == 0)
	{
		dir = find_node_aarij(shell->environ->env, "OLDPWD");
		if (dir == NULL)
			printf("cd: OLDPWD not set\n");
	}
	else
		dir = shell->exec[i]->cmd[1];
	return (dir);
}

char	*find_node_aarij(t_values *temp, char *target_key)
{
	t_values	*travel;

	if (temp)
	{
		travel = temp;
		while (travel)
		{
			if (!ft_strncmp(target_key, travel->key, ft_strlen(travel->key)))
				return (travel->value);
			travel = travel->next;
		}
	}
	return (NULL);
}

int	update_pwd(t_shell *shell, char *directory)
{
	t_values	*temp;
	t_values	*temp2;

	temp = locate_node(shell->environ->env, "PWD");
	temp2 = locate_node(shell->environ->env, "OLDPWD");
	if (temp)
	{
		if (temp2)
			if (change_nodeee(temp2, temp->value) == 1)
				return (ft_free((void **)&directory), 1);
		if (change_nodeee(temp, directory) == 1)
			return (ft_free((void **)&directory), 1);
	}
	return (0);
}

int	change_nodeee(t_values *node, char *new)
{
	ft_free((void **)&node->value);
	ft_free((void **)&node->string);
	node->value = ft_strdup(new);
	node->string = ft_strjoin2(node->key, "=", node->value);
	if (node->string)
		return (0);
	else
		return (1);
}
