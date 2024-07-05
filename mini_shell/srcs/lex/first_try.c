/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_try.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:48:04 by tabadawi          #+#    #+#             */
/*   Updated: 2024/07/05 22:05:20 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief gets the last node in a lis
/// @param lst the head
/// @return a pointer to the last node
t_noding	*last_node(t_noding *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/// @brief gets the node thats right before a partiular node
/// @param shell 
/// @param target the node u wanna find what behind it is
/// @return the pointer to the node
t_noding *prev_node(t_shell *shell, t_noding *target)
{
	t_noding	*traveler;
	
	traveler = NULL;
	if (!shell->parser->noding || !target)
		return (NULL);
	if (shell->parser->noding)
	{
		traveler = shell->parser->noding;
		while (traveler->next && traveler->next != target)
			traveler = traveler->next;
	}
	return (traveler);
}

/// @brief checks if the previous node was an operater
/// @param shell 
/// @return true or false
int	invalid_token(t_shell *shell)
{
	if (!shell->parser->noding || !last_node(shell->parser->noding))
		return (0);
		// last_node(shell->parser->noding)->type == pipes
	if (
	last_node(shell->parser->noding)->type == inp_redir
	|| last_node(shell->parser->noding)->type == opt_redir
	|| last_node(shell->parser->noding)->type == append
	|| last_node(shell->parser->noding)->type == here_doc)
	{
		return (1);
	}	
	else if (last_node(shell->parser->noding)->type == space)
	{
		if (!prev_node(shell, last_node(shell->parser->noding))
		// || prev_node(shell, last_node(shell->parser->noding))->type == pipes
		|| prev_node(shell, last_node(shell->parser->noding))->type == inp_redir
		|| prev_node(shell, last_node(shell->parser->noding))->type == opt_redir
		|| prev_node(shell, last_node(shell->parser->noding))->type == append
		|| prev_node(shell, last_node(shell->parser->noding))->type == here_doc)
		{
			return (1);	
		}
	}
	return (0);
}
//this function^^ was checking for pipes too
//had to remove that cuz operators could come after pipes



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


/// @brief adds a node to a linked list
/// @param shell 
/// @param  
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
	// (void)shell;
	t_noding *new;
	
	(void)str;
	new = malloc(sizeof(t_noding));
	new->next = NULL;
	new->shell = shell;
	new->value = ft_strdup("|");
	// if (!invalid_token(shell))
	// 	new->type = pipes;
	// if (!shell->parser->noding)
	// 	new->type = invalid;
	// else
	// 	new->type = invalid;

	//had to manually check here for previous nodes if they were pipes
	if (invalid_token(shell) || !shell->parser->noding || last_node(shell->parser->noding)->type == pipes
	|| (last_node(shell->parser->noding)->type == space && prev_node(shell, last_node(shell->parser->noding))->type == pipes))
		new->type = invalid;
	else
		new->type = pipes;
	token_node(shell, new);
	// printf("|	:	pipe\n");
	return (index);
}

int	assign_redirection(char *str, int index, t_shell *shell)
{
	t_noding *new;
	new = malloc(sizeof(t_noding));
	new->next = NULL;
	new->shell = shell;
	if (str[index + 1] == str[index])
	{
		if (str[index] == '>')
		{
			if (!invalid_token(shell))
				new->type = append;
			else
				new->type = invalid;
			new->value = ft_strdup(">>");
			// printf(">>	:	append\n");
		}
		else if (str[index] == '<')
		{
			if (!invalid_token(shell))
				new->type = here_doc;
			else
				new->type = invalid;
			new->value = ft_strdup("<<");
			// printf("<<	:	heredoc\n");
		}
		index++;
	}
	else if (str[index + 1] != str[index])
	{
		if (str[index] == '>')
		{
			if (!invalid_token(shell))
				new->type = opt_redir;
			else
				new->type = invalid;
			new->value = ft_strdup(">");
			// printf(">	:	output redirection\n");
		}
		else if (str[index] == '<')
		{	
			if (!invalid_token(shell))
				new->type = inp_redir;
			else
				new->type = invalid;
			new->value = ft_strdup("<");
			// printf("<	:	input redirection\n");	
		}
	}
	token_node(shell, new);
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
	// (void)shell;
	t_noding	*new;
	// int temp = index;
	while ((str[index] == ' ' || str[index] == '\t') && str[index] != '\0')
		index++;
	index--;
	new = malloc(sizeof(t_noding));
	new->next = NULL;
	new->shell = shell;
	new->type = space;
	new->value = ft_strdup(" ");
	token_node(shell, new);
	// printf("we have (%d) spaces\n", index - temp + 1);
	return (index);
}

int	assign_word(char *str, int index, t_shell *shell)
{
	t_noding *new;
	new = malloc(sizeof(t_noding));
	new->next = NULL;
	new->shell = shell;
	new->type = option;
	int temp = index;
	while (!delimeter(str[index + 1]))
		index++;
	int j = 0;
	new->value = malloc(sizeof(char) * (index - temp + 2));
	while (temp <= index)
	{
		new->value[j] = str[temp];
		j++;
		temp++;
	}
	new->value[j] = '\0';
	j = 0;
	token_node(shell, new);
	// printf("this is a word : (%s)\n", new->value);
	return (index);
}

int check_invalid(char *str, int i, t_shell *shell)
{
	(void)shell;
	i++;
	if (str[i] != '_' && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
		return (-1);
	while (str[i]&& (str[i] == '_' || (str[i] >= '0' && str[i] <= '9')
	|| (str[i] >= 'a' & str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')))
		i++;
	return (i);
}

int		valid_name(char character, int current, int first)
{
	if (current == first)
	{
		if (!(character >= 'a' && character <= 'z') 
		&& !(character >= 'A' && character <= 'Z') && character != '_')
			return (0);	
	}
	else
	{	
		if (!(character >= 'a' && character <= 'z') &&
		!(character >= 'A' && character <= 'Z') && character != '_'
		&& !(character >= '0' && character <= '9'))
			return (0);
	}
	return (1);
}

int		assign_variable(char *str, int index, t_shell *shell)
{
	t_noding *new;
	int temp;
	int	j = 0;
	if (str[index + 1] == ' ' || str[index + 1] == '\t' || str[index + 1] == '\0')
		return ((void)printf("just a $\n"), index);
	new = malloc(sizeof(t_noding));
	new->next = NULL;
	new->shell = shell;
	new->type = variable;
	temp = index;
	while (str[index + 1] && valid_name(str[index + 1], index + 1, temp + 1))
		index++;
	new->value = malloc(sizeof(char) * (index - temp + 3));
	new->value[j++] = '$';
	while (temp++ < index)
		new->value[j++] = str[temp];
	new->value[j++] = '\0';
	token_node(shell, new);
	// printf("this is a variable (%s)\n", variable);
	return(index);
}

int		assign_quotes(char *str, int index, t_shell *shell)
{
	t_noding	*new;
	new = malloc(sizeof(t_noding));
	new->shell = shell;
	new->next = NULL;
	new->value = NULL;
	int temp = index;
	int j = 0;
	int counter = 0;
	if (str[index] == '"')
	{
		counter += 1;
		while (str[index + 1] && str[index + 1] != '"' && str[index])
			index++;
		if(str[index + 1] == '"')
		{
			index++;
			counter += 1;
		}
		new->value = malloc(sizeof(char) * (index - temp + 2));
		while (temp <= index)
			new->value[j++] = str[temp++];
		new->value[j] = '\0';
		if (counter != 2)
			new->type = invalid;
		else
			new->type = dqoutes;
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
			temp++;
		}
		new->value = malloc(sizeof(char) * (index - temp + 1));
		while (temp < index)
			new->value[j++] = str[temp++];
		new->value[j] = '\0';
		if (counter != 2)
			new->type = invalid;
		else
			new->type = option;
		//removed sqoutes from enum, sqoutes technically are just words
		//also removed the sqoutes characters 
	}
	token_node(shell, new);
	// printf("string	:	(%s)\n", new->value);
	return (index);
}


void	test(t_noding *traveler, t_tokens actual_token)
{
	if (traveler->next && traveler->next->type == option)
	{
		printf("\n\nCONDITION 1\n\n");
		traveler->next->type = actual_token;
	}
	else if (traveler->next && traveler->next->type == space)
	{
		printf("\n\nCONDITION 2\n\n");
		if (traveler->next->next && traveler->next->next->type == option)
			traveler->next->next->type = actual_token;
		else
			traveler->type = invalid;
	}
	else
	{
		printf("\n\nCONDITION 3\n\n");
		traveler->type = invalid;
	}
}

//very rough function that for now assigns the correct destination/source
//of redirections, need to shorten it and do more things 
void	she_asked_for_a_second_round(t_shell *shell)
{
	t_noding	*traveler;
	if (!shell->parser || !shell->parser->noding)
		return ;
	traveler = shell->parser->noding;
	while (traveler)
	{
		//i managed to make it shorter by creating this pattern as a function 
		if (traveler->type == inp_redir)
			test(traveler, inp_file);
		else if (traveler->type == opt_redir || traveler->type == append)
			test(traveler, opt_file);
		else if (traveler->type == here_doc)
			test(traveler, delimiter);
		traveler = traveler->next;
	}
}

void	recieve_str(t_shell *shell, char *str)
{
	(void)shell;
	int	i = 0;
	shell->parser = NULL;
	if (!str)
		return ;
	shell->parser = malloc(sizeof(t_parser));
	shell->parser->noding = NULL;
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
	//i think smth else should happen first
	//we need to make sure that whatever comes after a heredoc is a delimeter
	//regardless of the token, we need to join and expand accordingly tokenize
	//as needed again
	//and also join the tokens accordingly
	//also i dont feel like working rn at all ill see what i can do tmrw. 
	she_asked_for_a_second_round(shell);
	t_noding *test;
	test = shell->parser->noding;
	while (test)
	{
		printf("%s		:		%u\n", test->value, test->type);
		test = test->next;
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