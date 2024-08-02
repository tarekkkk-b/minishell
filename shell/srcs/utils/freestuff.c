/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:43:51 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/02 15:03:14 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freetwodarray(char **str)
{
	int i = -1;
	if (!str)
		return ;
	while (str[++i])
		ft_free((void **)&str[i]);
	ft_free((void **)str);
}

void	free_env(t_shell *shell)
{
	t_values	*temp;

	while (shell->environ->env != NULL)
	{
		temp = shell->environ->env;
		shell->environ->env = shell->environ->env->next;
		ft_free((void **)&temp->key);
		ft_free((void **)&temp->value);
		ft_free((void **)&temp->string);
		ft_free((void **)&temp);
	}
	ft_free((void **)&shell->environ->cwd);
	ft_free((void **)&shell->environ->owd);
	ft_free((void **)&shell->environ);
}

void	mass_free(t_shell *shell, int exit_code)
{
	int i = 0;
	if (shell->environ)
		if (shell->environ->env)
			free_env(shell);
	if (shell->parser)
		if (shell->parser->noding)
			free_tokenization(shell);
	if (shell->exec)
	{
		while (shell->exec[i])
		{
			ft_free ((void **)shell->exec[i]->cmdpath);	
			freetwodarray(shell->exec[i]->cmd);
			freetwodarray(shell->exec[i]->inp_files);
			freetwodarray(shell->exec[i]->opt_files);
			ft_free((void **)&shell->exec[i]->inp_flags);
			ft_free((void **)&shell->exec[i]->opt_flags);
			ft_free((void **)&shell->exec[i]);
			i++;
		}
		free(shell->exec);
	}
	ft_close(shell, &shell->fd);
	exit(exit_code);
}

void	free_tokenization(t_shell *shell)
{
	t_noding	*temp;
	t_noding	*temp2;

	if (shell->parser->noding)
	{
		temp = shell->parser->noding;
		while (temp)
		{
			temp2 = temp->next;
			ft_free((void **)&temp->value);
			ft_free((void **)&temp);
			temp = temp2;
		}
	}
	ft_free((void **)&shell->parser);
}
