/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:43:51 by ahaarij           #+#    #+#             */
/*   Updated: 2024/07/16 12:35:25 by ahaarij          ###   ########.fr       */
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
        free(temp->key);
        free(temp->value);
        free(temp->string);
        free(temp);
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
//         free(node->key);
//         free(node->value);
//         free(node->string);
//     }
// }
