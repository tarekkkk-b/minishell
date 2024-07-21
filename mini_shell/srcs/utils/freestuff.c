/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:43:51 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/21 14:24:45 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_values(t_values *env)
{
    t_values *temp;

    while(env != NULL)
    {
        temp = env;
        env = env->next;
        ft_free((void **)&temp->key);
        ft_free((void **)&temp->value);
        ft_free((void **)&temp->string);
        ft_free((void **)&temp);
    }
}

// void    free_list(t_values *head)
// {
//     t_values    *temp;

//     if (head)
//     {
//         while (head)
//         {
//             temp = head->next;
//             free_node(head);
//             head = temp;
//         }
//     }
// }

// void    free_node(t_values *node)
// {
//     if (node)
//     {
//         ft_free((void **)&node->key);
//         ft_free((void **)&node->value);
//         ft_free((void **)&node->string);
//     }
// }
