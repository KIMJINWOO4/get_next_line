/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwokim <jinwokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:33:42 by gimjin-u          #+#    #+#             */
/*   Updated: 2023/04/17 17:00:48 by jinwokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	str_len;

	str_len = 0;
	while (*s++)
		str_len++;
	return (str_len);
}

char	*free_str(void *result, t_list **tmp)
{
	t_list	*tmp2;

	if (tmp)
	{
		tmp2 = *tmp;
		free(tmp2->line);
		free(*tmp);
		*tmp = 0;
		return (0);
	}
	free(result);
	return (0);
}

char	*get_next(int fd, char *result)
{
	char	*buf;
	int		i;

	i = 1;
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free_str(result, 0));
	while (!ft_strchr(result, '\n') && i != 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(buf);
			return (free_str(result, 0));
		}
		if (!i)
			break ;
		*(buf + i) = '\0';
		result = ft_strjoin(result, buf);
		if (!result)
			return (free_str(buf, 0));
	}
	free(buf);
	return (result);
}

char	*get_next_line(int fd)
{
	static t_list	*result;
	char			*put_line;

	if (!result)
	{
		result = (t_list *)malloc(sizeof(t_list));
		if (!result)
			return (0);
		result->line = NULL;
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	result->line = get_next(fd, result->line);
	if (!result->line)
		return (free_str(0, &result));
	put_line = ft_get_line(result->line);
	if (put_line != 0)
		result->line = keep_next_line(result->line);
	else
		return (free_str(0, &result));
	return (put_line);
}
