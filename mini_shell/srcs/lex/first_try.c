/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:48:04 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/23 19:47:29 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_noding	*last_node(t_noding *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	token_node(t_shell *shell, t_noding *new)
{
	t_noding	*temp;

	if (shell->parser->noding)
	{
		temp = last_node(shell->parser->noding);
		temp->next = new;
	}
	else
		shell->parser->noding = new;
}

int	assigne_pipe(char *str, int index, t_shell *shell)
{
	(void)shell;
	(void)str;
	printf("|	:	pipe\n");
	return (index);
}

int	assigne_redirection(char *str, int index, t_shell *shell)
{
	(void)shell;
	if (str[index + 1] == str[index])
	{
		if (str[index] == '>')
			printf(">>	:	append\n");
		else if (str[index] == '<')
			printf("<<	:	heredoc\n");
		index++;
	}
	else if (str[index + 1] != str[index])
	{
		if (str[index] == '>')
			printf(">	:	output redirection\n");
		else if (str[index] == '<')
			printf("<	:	input redirection\n");	
	}
	return (index);
}

int	assigne_space(char *str, int index, t_shell *shell)
{
	(void)shell;
	int temp = index;
	while ((str[index] == ' ' || str[index] == '\t') && str[index] != '\0')
		index++;
	index--;
	printf("we have (%d) spaces\n", index - temp + 1);
	return (index);
}

int	assigne_word(char *str, int index, t_shell *shell)
{
	(void)shell;
	(void)str;
	char *string = NULL;
	int temp = index;
	while (str[index + 1] != '>' && str[index + 1] != '<' && str[index + 1] != ' ' && str[index + 1] != '\t'
		&& str[index + 1] != '$' && str[index + 1] != '|' && str[index + 1] != '\0')
		index++;
	int j = 0;
	string = malloc(sizeof(char) * (index - temp + 2));
	while (temp <= index)
	{
		string[j] = str[temp];
		j++;
		temp++;
	}
	string[j] = '\0';
	printf("this is a word : (%s)\n", string);
	return (index);
}

void	recieve_str(t_shell *shell, char *str)
{
	(void)shell;
	int	i = 0;
	shell->parser = malloc(sizeof(t_parser));
	while (str[i])
	{
		if (str[i] == '|')
			i = assigne_pipe(str, i, shell);
		else if (str[i] == '>' || str[i] == '<')
			i = assigne_redirection(str, i, shell);
		else if (str[i] == ' ' | str[i] == '\t')
			i = assigne_space(str, i, shell);
		// else if (str[i] == '$')
		// 	assigne_variable()
		else
			i = assigne_word(str, i, shell);
		i++;
	}
}