/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:20:12 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/23 17:59:37 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

/**
Casting BUFFER_SIZE + 1 to ssize_t because with INT_MAX
as BUFFER_SIZE is defined as an int, it overflows as a 32 bits
value before being given to malloc which awaits a 64 values.
*/
void	*read_file(int fd, char *buffer)
{
	char		*temp;
	ssize_t		n_byte;

	temp = malloc((ssize_t)BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		n_byte = read(fd, temp, (ssize_t)BUFFER_SIZE);
		if (n_byte == -1)
			return (free_2x(buffer, temp));
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
	char		*line;
	char		*newline_pos;
	size_t		len;
	size_t		i;

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
	char		*newbuffer;
	char		*newline_pos;
	size_t		i;
	size_t		j;

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

/**
Could create my buffer with 
static char buffer[BUFFER_SIZE]; 
but i'd be stack dependent. I did prefer to 
allocate so if BUFFER_SIZE > 8388608
the program will still work
*/
char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FD_MAX)
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
