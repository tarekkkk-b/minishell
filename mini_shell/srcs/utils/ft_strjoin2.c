/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:00:14 by ahaarij           #+#    #+#             */
/*   Updated: 2024/06/18 21:24:42 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_strjoin2(char *str1, char *str2, char *str3)
{
	char	*new;
	int		i;
	int		j;
	int		k;
	if(!str1 && !str3)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	new = malloc((ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3)) + 1);
	if (!new)
		return (NULL);
	while(str1[i])
	{
		new[i] = str1[i];
		i++;
	}
	while(str2 != NULL && str2[j])
		new[i++] = str2[j++];
	while(str3[k])
		new[i++] = str3[k++];
	new[i] = '\0';
	return (new);
}
