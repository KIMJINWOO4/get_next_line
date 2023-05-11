/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwokim <jinwokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:57:56 by jinwokim          #+#    #+#             */
/*   Updated: 2023/04/15 19:35:41 by jinwokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	sum;
	size_t	i;
	char	*tmp;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		if (!s1)
			return (0);
		*(s1) = '\0';
	}
	if (!s2)
		return (free_str(s1, 0));
	i = ft_strlen(s1);
	sum = i + ft_strlen(s2);
	tmp = (char *)malloc(sum + 1);
	if (!tmp)
		return (free_str(s1, 0));
	ft_strlcpy(tmp, s1, sum + 1);
	ft_strlcpy(tmp + i, s2, sum + 1);
	free(s1);
	return (tmp);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	index;

	index = 0;
	if (!s)
		return (0);
	while ((*(s + index) != (char)c) && *(s + index))
		index++;
	if (*(s + index) || !(char)c)
		return ((char *)s + index);
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (*(src + i))
		i++;
	if (!dest)
		return (i);
	while (j + 1 < size && j < i)
	{
		*(dest + j) = *(src + j);
		j++;
	}
	if (size > 0)
		*(dest + j) = '\0';
	return (i);
}

char	*ft_get_line(char *result)
{
	char	*new_line;
	char	*arr;
	size_t	i;

	if (!*(result))
		return (0);
	new_line = ft_strchr(result, '\n');
	i = ft_strlen(result);
	if (!new_line)
	{
		new_line = (char *)malloc(i + 1);
		if (!new_line)
			return (0);
		ft_strlcpy(new_line, result, i + 1);
		return (new_line);
	}
	arr = (char *)malloc(new_line - result + 2);
	if (arr == 0)
		return (0);
	ft_strlcpy(arr, result, (new_line - result + 2));
	return (arr);
}

char	*keep_next_line(char *result)
{
	char	*next_line;
	char	*tmp;
	size_t	i;

	if (!result)
		return (0);
	next_line = ft_strchr(result, '\n');
	if (next_line)
	{
		next_line++;
		i = ft_strlen(next_line);
		if (!i)
			return (free_str(result, 0));
		tmp = (char *)malloc(i + 1);
		if (!tmp)
			return (free_str(result, 0));
		ft_strlcpy(tmp, next_line, i + 1);
		free(result);
		return (tmp);
	}
	return (free_str(result, 0));
}
