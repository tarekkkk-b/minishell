/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:48:04 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/29 15:17:04 by tabadawi         ###   ########.fr       */
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

int	invalid_chars(char c)
{
	char invalid[] = {'&',';','\\', '*', '(', ')'};
	int i = 0;
	int invalidcheck = 0;
	int invalid_length = sizeof(invalid) / sizeof(invalid[0]);
	while(i < invalid_length && invalidcheck != 1)
	{
		if(c != invalid[i])
			i++;
		else
			invalidcheck = 1;
	}
	if(invalidcheck == 1)
		return (1);
	return (0);
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

int	delimeter(char character)
{
	if (character == '>' || character == '<' || character == ' '
	|| character == '\t' || character == '\'' || character == '"'
	|| character == '|' || character == '\0' || character == ';'
	|| character == '\\' || character == ')' || character == '('
	|| character == '$'|| character == '&' || character == '*')
		return (1);
	return (0);
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
	while (!delimeter(str[index + 1]))
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
	j = 0;
	printf("this is a word : (%s)\n", string);
	return (index);
}

int check_invalid(char *str, int i, t_shell *shell)
{
	(void)shell;
	// int starting = i;
	// i += 1;
	// if((str[0] && !(str[0] >= 0 && str[starting] <= 9)) && ((str[0] == '?') || (str[0] >= 'A' && str[0] <= 'Z') || (str[0] >= 'a' && str[0] <= 'z')))
	// {
	// 	while(str[i] && (((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) || (str[i] >= 0 && str[i] <= 9)))
	// 		i++;
	// 	return (i);
	// }
	// return (-1);
	i++;
	if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
		return (-1);
	while (str[i]&& (str[i] == '_' || (str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' & str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	return (i);
}

// int	assign_variable(char *str, int index, t_shell *shell)
// {
// 	(void)shell;
// 	int	temp;
// 	char *variable;
// 	if (str[index + 1] == ' ' || str[index + 1] == '\t' || str[index + 1]== '\0')
// 	{
// 		printf("this is a word : ($)\n");
// 		return (index);
// 	}
// 	temp = index;
// 	index++;
// 	while (!delimeter(str[index + 1]))
// 		index++;
// 	int j = 0;
// 	variable = malloc(sizeof(char) * (index - temp + 2));
// 	while (temp <= index)
// 	{
// 		variable[j] = str[temp];
// 		j++;
// 		temp++;
// 	}
// 	variable[j] = '\0';
// 	if(check_invalid(variable, 0, shell) != -1)
// 		printf("This is a valid variable : (%s)\n", variable);
// 	else
// 		printf("this is an invalid variable : (%s)\n", variable);
// 	return (index);
// }

int		assign_variable(char *str, int index, t_shell *shell)
{
	(void)shell;
	int temp;
	if (str[index + 1] == ' ' || str[index + 1] == '\t' || str[index + 1] == '\0')
		return ((void)printf("just a $\n"), index);
	temp = index;
	while (str[index + 1])
		index++;
	return(index);
}

int		assign_quotes(char *str, int index, t_shell *shell)
{
	(void)shell;
	int temp = index;
	char *string = NULL;
	int j = 0;
	int counter = 0;
	if (str[index] == '"')
	{
		counter += 1;
		while (str[index + 1] && str[index + 1] != '"' && str[index])
			index++;
		if(str[index + 1] == '"'){
			index++;
			counter += 1;
		}
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
		counter += 1;
		while (str[index + 1] && str[index + 1] != '\'' && str[index])
			index++;
		if(str[index + 1] == '\'')
		{
			index++;
			counter += 1;
		}
		string = malloc(sizeof(char) * (index - temp + 2));
		while (temp <= index)
		{
			string[j] = str[temp];
			j++;
			temp++;
		}
		string[j] = '\0';
	}
	printf("string	:	(%s)\n", string);
	if (counter != 2)
		return ((void)printf("This shit dont work\n"), index);
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
		else if (invalid_chars(str[i]) == 1)
			printf("this is an invalid character : (%c)\n", str[i]);
		else
			i = assign_word(str, i, shell);
		i++;
	}
}

// invalid chars are just chars we dont need to handle;
// invalid variable name is just variable names that need to be valid

//general meta characters in ascii

//0 - 47
//58 - 64
//91 - 96
//123 - 127

//new note this ^^ isnt very accurate


//also i realized we were handling the variables thing wrong
//the validity of a variable should be checkeed upon creatin, the way to tell
//if a variable is being created is by the =, cuz u create and assign instantly,
//and this just sparked 2 ideas in my head rn ill say them rq in a sec, when a dollar
//sign is there tho we read after the $ till we find a delimeter then we check in the
//env if that var exists (even if it was an invalid name)

//two ideas
//1- we go thru a word, not treating the = as a delimeter, if we find an = sign
//right after, that means left is a variable name (and we need to check its validity)
//and right is value
//2- store as variable and value

//new note that was added, just realized not everything here is an invalid character
//or a meta character, if i do _ only its gonna take it as a word, it could be invalid
//or just an option for a cmd


//it is safe to say that 0-32 are not allowed also 127
// invalid: &, (, ), *, ;, \,


//things are getting quite confusing rn but ill research more tmrw

//I FIGURED IT OUT