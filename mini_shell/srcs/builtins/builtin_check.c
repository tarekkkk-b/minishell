/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:57:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/23 13:24:24 by ahaarij          ###   ########.fr       */
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

int	builtin_check(t_shell *shell)
{
	int i = 0;
	int args_c = 0;
	while(shell->exec[i])
	{
		args_c = args_count(shell, i);
		if (ft_strncmp(shell->exec[i]->cmd[0], "env", 4) == 0)
			builtin_env(shell->environ);
		if (ft_strncmp(shell->exec[i]->cmd[0], "pwd", 4) == 0)
			builtin_pwd(shell);
		if (ft_strncmp(shell->exec[i]->cmd[0], "cd", 3) == 0)
			builtin_cd(shell, i, args_c);
		if(ft_strncmp(shell->exec[i]->cmd[0], "echo", 5) == 0)
			builtin_echo(shell, i);
		if(ft_strncmp(shell->exec[i]->cmd[0], "exit", 5) == 0)
			builtin_exit(shell, args_c, i);
		i++;
	}
	return (0);
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