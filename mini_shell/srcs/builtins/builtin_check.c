/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:57:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/21 13:43:26 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_check(t_shell *shell)
{
    // if(!shell->str || !shell)
    //     if(builtin_exit(shell) == 1) // takes in argc, argv, actually all of tem take argc argv.
    //         return (1);
    if(ft_strncmp(shell->str, "env", 3) == 0)
        builtin_env(shell->environ);
    // if(ft_strncmp(shell->str, "exit", 4) == 0)
    //     if((builtin_exit(shell)) == 1)
    //         return (1);
    if(ft_strncmp(shell->str, "pwd", 4) == 0)
        builtin_pwd(shell);
    if(ft_strncmp(shell->str, "cd", 3) == 0)
        builtin_cd(shell);
    // if(ft_strncmp(shell->str, "echo", 4) == 0)
    //     builtin_echo(shell->str);
    // ECHO DOES NOT WORK, BUT I HAVE AN IDEA NOW, WILL WORK ON IT TOMORROW AFTER I EXPLAIN SMTH
    
    return(0);
}