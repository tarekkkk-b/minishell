/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:54:05 by ahaarij           #+#    #+#             */
/*   Updated: 2024/08/11 12:54:28 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (1);
	i = -1;
	if (ft_strlen(str1) == ft_strlen(str2))
	{
		while (str1[++i])
			if (str1[i] != str2[i])
				return (1);
	}
	else
		return (1);
	return (0);
}
