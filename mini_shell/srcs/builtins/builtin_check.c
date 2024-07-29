/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:57:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/29 18:14:21 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	args_count(t_shell *shell, int index)
{
	int i = 0;
	while (shell->exec[index]->cmd[i])
		i++;
	return i;	
}

int	mass_check(char *str)
{
	int i = 0;
	static char *string[8] = {
		"env", "pwd", "cd", "echo", "exit", "export", "unset"
	};
	while (str && string[i])
	{
		if (ft_strncmp(str, string[i], (ft_strlen(string[i]) + 1)) == 0)
			return(1);
		i++; 
	}
	return (0);
}

int	builtin_check(t_shell *shell, int index, int flag)
{
	int	exit_code = 0;
	int args_c = 0;
	if (!shell || !shell->exec)
		return (-1);
	if (flag)
	{
		// if a pipe occurs 
		// if theres only one set of commands, ie no pipe, and if its not a builtin, exit, but exit doesnt seem right, wouldnt return fit?
		if (!(shell->exec[1]) && mass_check(shell->exec[index]->cmd[0]) == 1)
			exit (0);
		if (!(shell->exec[1]) || mass_check(shell->exec[index]->cmd[0]) == 0)
			return (1);
		args_c = args_count(shell, index);
		if (ft_strncmp(shell->exec[index]->cmd[0], "env", 4) == 0)
			exit_code = builtin_env(shell->environ);
		else if (ft_strncmp(shell->exec[index]->cmd[0], "pwd", 4) == 0)
			exit_code = builtin_pwd(shell);
		else if (ft_strncmp(shell->exec[index]->cmd[0], "cd", 3) == 0)
			exit_code = builtin_cd(shell, index, args_c);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "echo", 5) == 0)
			exit_code = builtin_echo(shell, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "exit", 5) == 0)
			exit_code = builtin_exit(shell, args_c, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "export", 5) == 0)
			export(args_c, shell, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "unset", 6) == 0)
			exit_code = builtin_unset(shell, args_c, index);
		exit(exit_code);
	}
	else if (!flag)
	{
		// if the amount of commands is greater than one, and its valid? what?
		if (shell->exec[0] && shell->exec[1])
			return (1);
		args_c = args_count(shell, index);
		if (ft_strncmp(shell->exec[index]->cmd[0], "env", 4) == 0)
			exit_code = builtin_env(shell->environ);
		else if (ft_strncmp(shell->exec[index]->cmd[0], "pwd", 4) == 0)
			exit_code = builtin_pwd(shell);
		else if (ft_strncmp(shell->exec[index]->cmd[0], "cd", 3) == 0)
			exit_code = builtin_cd(shell, index, args_c);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "echo", 5) == 0)
			exit_code = builtin_echo(shell, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "exit", 5) == 0)
			exit_code = builtin_exit(shell, args_c, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "export", 5) == 0)
			export(args_c, shell, index);
		else if(ft_strncmp(shell->exec[index]->cmd[0], "unset", 6) == 0)
			exit_code = builtin_unset(shell, args_c, index);
	}
	return (1);
}


// int	builtin_check(t_shell *shell)
// {
// 	if(!shell->str || !shell)
// 	    if(builtin_exit(shell) == 1) // takes in argc, argv, 
// 		actually all of tem take argc argv.
// 	        return (1);
// 	if (ft_strncmp(shell->str, "env", 3) == 0)
// 		builtin_env(shell->environ);
// 	if(ft_strncmp(shell->str, "exit", 4) == 0)
// 	    if((builtin_exit(shell)) == 1)
// 	        return (1);
// 	if (ft_strncmp(shell->str, "pwd", 4) == 0)
// 		builtin_pwd(shell);
// 	if (ft_strncmp(shell->str, "cd", 3) == 0)
// 		builtin_cd(shell);
// 	if(ft_strncmp(shell->str, "echo", 4) == 0)
// 	    builtin_echo(shell->str);
// 	ECHO DOES NOT WORK, BUT I HAVE AN IDEA NOW, 
//	WILL WORK ON IT TOMORROW AFTER I EXPLAIN SMTH
// 	return (0);
// }