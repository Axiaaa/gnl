/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:20:12 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/10 18:20:45 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*read_file(int fd, char *buffer)
{
	char	*temp;
	int		n_byte;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		n_byte = read(fd, temp, BUFFER_SIZE);
		if (n_byte == -1)
			return (free_2x(buffer, temp), NULL);
		if (n_byte == 0)
			break ;
		temp[n_byte] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
		{
			free_2x(temp, buffer);
			buffer = NULL;
			return (NULL);
		}
	}
	free(temp);
	return (buffer);
}

void	*get_before_nl(char *buffer)
{
	char	*line;
	char	*newline_pos;
	int		len;
	int		i;

	if (!buffer)
		return (NULL);
	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
		len = newline_pos - buffer + 1;
	else
		len = ft_strlen(buffer);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && i < len)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_after_nl(char *buffer)
{
	char	*newbuffer;
	char	*newline_pos;
	int		i;
	int		j;

	newline_pos = ft_strchr(buffer, '\n');
	if (!newline_pos)
	{
		free(buffer);
		return (NULL);
	}
	i = (newline_pos - buffer) + 1;
	j = 0;
	newbuffer = malloc(ft_strlen(buffer) - i + 1);
	if (!newbuffer)
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i])
		newbuffer[j++] = buffer[i++];
	newbuffer[j] = '\0';
	free(buffer);
	return (newbuffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (buffer[fd] != NULL && *buffer[fd])
	{
		line = get_before_nl(buffer[fd]);
		if (!line)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		buffer[fd] = get_after_nl(buffer[fd]);
		return (line);
	}
	free(buffer[fd]);
	buffer[fd] = NULL;
	return (NULL);
}
