/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:08:39 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/15 13:47:38 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// like cd, this should take in argc argv, will add it once lsit is ready

// int builtin_exit(t_readline rl)
// {
// 	int exit_code;
	
// 	if(argc >= 2 && (ft_isdigit(argv[1]) == 1))
// 		exit_code = 255;
// 	else if(argc == 2)
		// exit_code = ft_atoi(argv[1]);
// 	else if(argc > 2)
// 	{
// 		printf("too many args");
// 		return (1);
// 	}
// 	// we need to have something that checks if we're in a child process, AND isatty;
// 	// we need to have something that frees everything also;
// 	exit(exit_code);
// }


int	is_num(char *str)
{
	int i = 0;
	if(!str[0])
	{
		printf("write something mane\n");
		return (1);
	}
	while(str[i] >= '0' && str[i] <= '9')
		i++;
	if(!str[i])
		return(0);
	return (1);
}


int builtin_exit(t_readline rl)
{
    write(0, "exit\n", 5);
	    if(kill(getpid(), 0) == 0)
	    {
	    	free(rl.path);
	    	free(rl.str);
	    	return(1);
	    }
	    return (1);
}