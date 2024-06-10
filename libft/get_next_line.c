/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:22:31 by tabadawi          #+#    #+#             */
/*   Updated: 2024/03/17 11:22:53 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_line(char *save)
{
	int		i;
	char	*print;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	print = malloc((sizeof(char)) * (i + 1 + (save[i] == '\n')));
	if (!print)
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		print[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		print[i] = '\n';
		i++;
	}
	print[i] = '\0';
	return (print);
}

static char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*buff;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	buff = malloc ((sizeof(char)) * ft_strlen(save) - i + 1);
	if (!buff)
		return (NULL);
	i++;
	j = 0;
	while (save[i])
		buff[j++] = save[i++];
	buff[j] = '\0';
	free(save);
	return (buff);
}

static char	*gnl_strjoin(char *sv, char *buff)
{
	char	*newsave;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!sv && !buff)
		return (NULL);
	newsave = malloc(sizeof(char) * ((ft_strlen(sv) + ft_strlen(buff)) + 1));
	if (!newsave)
		return (NULL);
	while (sv && sv[i] != '\0')
	{
		newsave[i] = sv[i];
		i++;
	}
	while (buff[j] != '\0')
		newsave[i++] = buff[j++];
	newsave[i++] = '\0';
	if (sv)
		free(sv);
	return (newsave);
}

char	*ft_readfile(char *save, int fd)
{
	int		rd;
	char	*buffer;

	buffer = malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	rd = 1;
	while (rd != 0 && ft_strchr(save, '\n') == 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
		{
			free(save);
			free(buffer);
			return (NULL);
		}
		buffer[rd] = '\0';
		save = gnl_strjoin(save, buffer);
	}
	free(buffer);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*print;
	static char	*save[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	save[fd] = ft_readfile(save[fd], fd);
	if (!save[fd])
		return (NULL);
	print = ft_get_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	return (print);
}
