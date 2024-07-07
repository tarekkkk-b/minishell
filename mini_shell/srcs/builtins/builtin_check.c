/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:57:20 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/07 14:26:35 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_check(t_readline rl, t_shell *shell)
{
    if(!rl.str || !shell)
        if(builtin_exit(rl) == 1)
            return (1);
    if(ft_strncmp(rl.str, "env", 3) == 0)
        builtin_env(shell->environ);
    if(ft_strncmp(rl.str, "exit", 4) == 0)
        if((builtin_exit(rl)) == 1)
            return (1);
    if(ft_strncmp(rl.str, "pwd", 4) == 0)
        builtin_pwd(shell);
    // if(ft_strncmp(rl.str, "echo", 4) == 0)
    //     builtin_echo(rl.str);
    // ECHO DOES NOT WORK, BUT I HAVE AN IDEA NOW, WILL WORK ON IT TOMORROW AFTER I EXPLAIN SMTH
    
    return(0);
}