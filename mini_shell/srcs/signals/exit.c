/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 01:18:48 by ahaarij           #+#    #+#             */
/*   Updated: 2024/06/25 12:26:50 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void    handle_sigint(int sig)
{
    (void)sig;
    // if (sig == SIGINT)
    // {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    // }
}

void    handle_sigquit(int sig)
{
    (void)sig;
    just_test();
}


int    signalhandler(void)
{
    signal(SIGINT, handle_sigint);
    // signal(SIGQUIT, handle_sigquit);
    signal(SIGABRT, handle_sigquit);
    signal(SIGQUIT, SIG_IGN);
    return (0);
}