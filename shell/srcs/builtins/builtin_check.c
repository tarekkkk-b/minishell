/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:57:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/10 13:45:54 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	args_count(t_shell *shell, int index)
{
	int	i;

	i = 0;
	while (shell->exec[index]->cmd[i])
		i++;
	return (i);
}

int	mass_check(char *str)
{
	int			i;
	static char	*string[8] = {
		"env", "pwd", "cd", "echo", "exit", "export", "unset"
	};

	i = 0;
	while (str && string[i])
	{
		if (ft_strncmp(str, string[i], (ft_strlen(string[i]) + 1)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	which_builtin(t_shell *shell, int index, int args_c)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp(shell->exec[index]->cmd[0], "env", 4) == 0)
		exit_code = builtin_env(shell->environ);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "pwd", 4) == 0)
		exit_code = builtin_pwd(shell);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "cd", 3) == 0)
		exit_code = builtin_cd(shell, index, args_c);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "echo", 5) == 0)
		exit_code = builtin_echo(shell, index, 1);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "exit", 5) == 0)
		exit_code = builtin_exit(shell, args_c, index);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "export", 5) == 0)
		export(args_c, shell, index);
	else if (ft_strncmp(shell->exec[index]->cmd[0], "unset", 6) == 0)
		exit_code = builtin_unset(shell, args_c, index);
	return (exit_code);
}

int	builtin_check(t_shell *shell, int index, int flag)
{
	int	temp_in;
	int	temp_out;
	int	args_c;

	args_c = 0;
	if (!shell || !shell->exec)
		return (-1);
	args_c = args_count(shell, index);
	if (flag)
	{
		if (!(shell->exec[1]) && mass_check(shell->exec[index]->cmd[0]))
			mass_free(shell, 0);
		if (!(shell->exec[1]) || !mass_check(shell->exec[index]->cmd[0]))
			return (1);
		shell->environ->exit = which_builtin(shell, index, args_c);
		mass_free(shell, shell->environ->exit);
	}
	else if (!flag)
	{
		if (!mass_check(shell->exec[index]->cmd[0]))
			return (1);
		if (shell->exec[0] && shell->exec[1])
			return (1);
		temp_in = dup(STDIN_FILENO);
		temp_out = dup(STDOUT_FILENO);
		inp_file_dup(shell->exec[index]);
		opt_file_dup(shell->exec[index]);
		shell->environ->exit = which_builtin(shell, index, args_c);
		dup2(temp_in, 0);
		dup2(temp_out, 1);
		ft_close(shell, &temp_in);
		ft_close(shell, &temp_out);
		return (shell->environ->exit);
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