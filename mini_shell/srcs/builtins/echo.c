/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:51:43 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/15 15:25:53 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// so you have everything split into args right, we just need to parse wherever its stored into this amd boom
// i texted u to ask but ur not here, so im just gonna finish for now, hehe finish... 🤤🤤
// also once i know about the args, the builtin checker will not need the strncmp like it does rn, ill be able to make it perfect.
// thanks
// im gonna go out for dinner w my family byee :D
// later but still bye
// ni
// what the hell tarek why would you write te n word
// because im racist and my name is tarek badawi i also ave a dog named togo hes racist too
// im tarek and im saying te n word look
// ni-
// TAREK NO DONT SAY THAT WAT TE HELL
// bye

// int builtin_echo(char *str)
// {
//     int flag = 0;
//     int i = 1;
//     while(args[i] && !ft_strncmp(args[i], "-n", 3))
//         i++;
//     if(i == 1)
//         flag = 1;
//     while(args[i])
//     {
//         ft_putstr_fd(args[i], 0);
//         if(args[i + 1])
//             write(1, " ", 1);
//         i++;
//     }
//     if(flag == 1)
//         write(1, "\n", 1);
//     return (0);
// }