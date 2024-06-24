/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:48:04 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/24 12:33:25 by tabadawi         ###   ########.fr       */
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

int	assign_pipe(char *str, int index, t_shell *shell)
{
	(void)shell;
	(void)str;
	printf("|	:	pipe\n");
	return (index);
}

int	assign_redirection(char *str, int index, t_shell *shell)
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

int	assign_space(char *str, int index, t_shell *shell)
{
	(void)shell;
	int temp = index;
	while ((str[index] == ' ' || str[index] == '\t') && str[index] != '\0')
		index++;
	index--;
	printf("we have (%d) spaces\n", index - temp + 1);
	return (index);
}

int	assign_word(char *str, int index, t_shell *shell)
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

int	assign_variable(char *str, int index, t_shell *shell)
{
	(void)shell;
	int	temp;
	char *variable;
	index++;
	temp = index;
	while (str[index + 1] != '>' && str[index + 1] != '<' && str[index + 1] != ' ' && str[index + 1] != '\t'
		&& str[index + 1] != '$' && str[index + 1] != '|' && str[index + 1] != '\0' && str[index + 1] != '-')
		index++;
	int j = 0;
	variable = malloc(sizeof(char) * (index - temp + 2));
	while (temp <= index)
	{
		variable[j] = str[temp];
		j++;
		temp++;
	}
	variable[j] = '\0';
	printf("this is a variable : (%s)\n", variable);
	return (index);
}

int		assign_quotes(char *str, int index, t_shell *shell)
{
	(void)shell;
	int temp = index;
	char *string = NULL;
	int j = 0;
	if (str[index] == '"')
	{
		while (str[index + 1] && str[index + 1] != '"')
			index++;
		index++;
		string = malloc(sizeof(char) * (index - temp + 2));
		while (temp <= index)
		{
			string[j] = str[temp];
			j++;
			temp++;
		}
		string[j] = '\0';
	}
	else if (str[index] == '\'')
	{
		while (str[index + 1] && str[index + 1] != '\'')
			index++;
		index++;
		string = malloc(sizeof(char) * (index - temp + 2));
		while (temp <= index)
		{
			string[j] = str[temp];
			j++;
			temp++;
		}
		string[j] = '\0';
	}
	printf("this is a string: (%s)\n", string);
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
			i = assign_pipe(str, i, shell);
		else if (str[i] == '>' || str[i] == '<')
			i = assign_redirection(str, i, shell);
		else if (str[i] == ' ' | str[i] == '\t')
			i = assign_space(str, i, shell);
		else if (str[i] == '$')
			i = assign_variable(str, i, shell);
		else if (str[i] == '"' || str[i] == '\'')
			i = assign_quotes(str, i, shell);
		else
			i = assign_word(str, i, shell);
		i++;
	}
}
