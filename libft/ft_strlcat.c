/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:27:47 by tabadawi          #+#    #+#             */
/*   Updated: 2023/12/04 14:36:39 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	s;
	size_t	t;
	size_t	destl;
	size_t	srcl;

	s = 0;
	t = 0;
	while (dest[t] != '\0')
		t++;
	destl = t;
	srcl = ft_strlen(src);
	if (dstsize == 0 || dstsize <= destl)
		return (srcl + dstsize);
	while (src[s] != '\0' && s < dstsize - destl - 1)
		dest[t++] = src[s++];
	dest[t] = '\0';
	return (destl + srcl);
}
