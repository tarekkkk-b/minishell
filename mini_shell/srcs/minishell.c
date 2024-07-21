/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:14:30 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/21 13:46:13 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_shell *shell)
{
	t_values	*tempe;
	t_values	*tempe2;

	if (shell->environ->env)
	{
		tempe = shell->environ->env;
		while (tempe)
		{
			tempe2 = tempe->next;
			free (tempe->value);
			free(tempe->key);
			free(tempe->string);
			free (tempe);
			tempe = tempe2;
		}
		free(shell->environ->cwd);
		shell->environ->cwd = NULL;
		free(shell->environ->owd);
		shell->environ->owd = NULL;
		free(shell->environ);
	}
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
			free (temp->value);
			free (temp);
			temp = temp2;
		}
	}
	free (shell->parser);
}

void	minishell(t_shell *shell)
{
	while (1)
	{
		signalhandler();
		free(shell->environ->cwd);
		shell->environ->cwd = getcwd(NULL, 0);
		shell->str = readline("𝓯𝓻𝓮𝓪𝓴𝔂𝓼𝓱𝓮𝓵𝓵 > ");
		if(!shell->str)
			break ;
		if (shell->str[0] != '\0')
			add_history(shell->str);
		if (parsing_hub(shell, shell->str))
			printf("tokenization succesful!\n");
		else
			printf("tokenization failed successfully!\n");
		free_tokenization(shell);
		free (shell->str);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		shell;

	shell.environ = NULL;
	(void)av;
	if (ac != 1)
		return (-1);
	printf("\e[1;1H\e[2J");
	create_env(env, &shell);
	minishell(&shell);
	free_env(&shell);
}
