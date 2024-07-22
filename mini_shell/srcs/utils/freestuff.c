/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:43:51 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/22 16:05:37 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (shell->environ)
		if (shell->environ->env)
			free_env(shell);
	if (shell->parser)
		if (shell->parser->noding)
			free_tokenization(shell);
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
