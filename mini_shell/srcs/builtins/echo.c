/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:51:43 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/22 09:58:37 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// so you have everything split into args right, 
// we just need to parse wherever its stored into this amd boom
// i texted u to ask but ur not here, so im just gonna finish for now
// also once i know about the args, 
// the builtin checker will not need the strncmp like it does rn

// int builtin_echo(char **argv)
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