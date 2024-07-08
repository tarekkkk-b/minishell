/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:08:39 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/08 15:44:55 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int builtin_exit(t_readline rl)
{
    write(0, "exit\n", 5);
	    if(kill(getpid(), 0) == 0)
	    {
	    	free(rl.path);
	    	free(rl.str);
	    	return(1);
	    }
	    return (0);
}