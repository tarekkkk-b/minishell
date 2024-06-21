/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 21:43:51 by ahaarij           #+#    #+#             */
/*   Updated: 2024/06/21 22:28:03 by ahaarij          ###   ########.fr       */
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

// if u dont tell me whats wrong i blow up your house