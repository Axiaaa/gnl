/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:20:12 by lcamerly          #+#    #+#             */
/*   Updated: 2025/04/09 22:18:07 by lcamerly         ###   ########.fr       */
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
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + (buffer[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_after_nl(char *buffer)
{
	char	*newbuffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
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
	static char	*buffer = NULL;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FD_MAX)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (buffer != NULL && *buffer)
	{
		line = get_before_nl(buffer);
		if (!line)
		{
			free(buffer);
			buffer = NULL;
		}
		buffer = get_after_nl(buffer);
		return (line);
	}
	free(buffer);
	buffer = NULL;
	return (NULL);
}
