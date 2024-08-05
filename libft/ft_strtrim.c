/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:47:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/08/05 21:28:38 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set, int flag)
{
	char	*new;
	int		start;
	int		end;
	int		i;

	start = 0;
	end = ft_strlen(s1);
	i = 0;
	while (s1[start] != '\0' && (checkset(s1[start], set) == 1))
		start++;
	while (end > start && (checkset(s1[end - 1], set) == 1))
		end--;
	new = (char *)malloc(sizeof(char) * ((end - start) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (start < end)
		new[i++] = s1[start++];
	new[i] = '\0';
	if (flag)
		free(s1);
	return (new);
}
