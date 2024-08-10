/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:51:23 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/10 15:08:05 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_cd(t_shell *shell, int i, int args)
{
	char	*directory;

	directory = get_directory(args, shell, i);
	if (directory == NULL)
		printf("nun");
	if (chdir(directory) == -1)
	{
		printf("cd: no such file or directory: %s\n", directory);
		return (1);
	}
	if (shell->exec[i]->cmd[i + 1] && \
	strncmp(shell->exec[i]->cmd[i + 1], "-", 2) == 0)
		printf("%s\n", directory);
	if (update_pwd(shell, getcwd(NULL, 0)) == 1)
	{
		printf("doesnt work\n");
		return (1);
	}
	return (0);
}

char	*get_directory(int args_count, t_shell *shell, int i)
{
	char	*dir;

	dir = NULL;
	if (args_count == 1)
	{
		dir = find_node_aarij(shell->environ->env, "HOME");
		if (dir == NULL)
			printf("HOME not set\n");
			// printf("exit code will be done 
			// i figure out how exit works");
	}
	else if (shell->exec[i]->cmd[1] && \
	strncmp(shell->exec[i]->cmd[1], "-", 2) == 0)
	{
		//add ft_
		dir = find_node_aarij(shell->environ->env, "OLDPWD");
		if (dir == NULL)
			printf("OLDPWD not set");
			// printf("exit code will be done once
			//i figure out how exit works");
	}
	else
		dir = shell->exec[i]->cmd[1];
//	// note to self
//	// uncomment this up portion once tarek finishes putting stuff in lists
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
		{
			if (change_nodeee(temp2, temp->value) == 1)
			{
				printf("Not work \n");
				return (1);
			}
		}
		if (change_nodeee(temp, directory) == 1)
		{
			printf("error\n");
			free(directory);
			return (1);
		}
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
