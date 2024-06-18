/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:00:14 by ahaarij           #+#    #+#             */
/*   Updated: 2024/06/18 17:40:19 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>






//  i left this file like this, if you want you can test it to see if its how you wanted it, if not lmk
// if its how you wanted it, remove the strlen int main and the extra headers and uncomment the main header file :)











size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

// this name is a placeholder for now, cuz ft_strjoin exists so just name it whatever you want

char    *strjoin_aarij(char *str1, char *str2, char *str3)
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

// int main()
// {
// 	char *a = "hello";
// 	// char *b = "there";
// 	char *c = "aarij";
// 	printf("%s", strjoin_aarij(a, NULL, c));
// }