/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcamerly <lcamerly@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:20:11 by lcamerly          #+#    #+#             */
/*   Updated: 2025/05/23 18:00:17 by lcamerly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void*	free_2x(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return NULL;
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	size_t	k;

	k = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 != NULL)
		k = ft_strlen(s1);
	ret = malloc(k + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i])
		ret[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i])
		ret[j++] = s2[i++];
	free((void *)s1);
	ret[j] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
