/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwokim <jinwokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 09:33:42 by gimjin-u          #+#    #+#             */
/*   Updated: 2023/04/19 20:25:43 by jinwokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlenfree(char *s, t_list **tmp, t_list *target)
{
	size_t	str_len;
	t_list	*tmp2;

	if (target)
	{
		tmp2 = *tmp;
		if (tmp2 == target)
			*tmp = target->next;
		else
		{
			while (tmp2->next != target)
				tmp2 = tmp2->next;
			tmp2->next = tmp2->next->next;
		}
		free(target->line);
		free(target);
		return (0);
	}
	str_len = 0;
	while (*s++)
		str_len++;
	return (str_len);
}

char	*free_str(void *result, t_list **tmp)
{
	t_list	*tmp2;
	t_list	*tmp3;

	if (tmp)
	{
		tmp2 = *tmp;
		tmp3 = *tmp;
		while (tmp2)
		{
			tmp3 = tmp3->next;
			free(tmp2->line);
			free(tmp2);
			tmp2 = tmp3;
		}
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

t_list	*find_fd(t_list **result, int fd)
{
	t_list	*tmp;

	tmp = *result;
	if (!tmp)
	{
		tmp = (t_list *)malloc(sizeof(t_list));
		if (!tmp)
			return (0);
		tmp->line = NULL;
		tmp->fd = fd;
		tmp->next = NULL;
		*result = tmp;
		return (tmp);
	}
	while (tmp && tmp->fd != fd && tmp->next)
		tmp = tmp->next;
	if (tmp && tmp->fd == fd)
		return (tmp);
	tmp->next = (t_list *)malloc(sizeof(t_list));
	if (!tmp->next)
		return (0);
	tmp->next->line = NULL;
	tmp->next->fd = fd;
	tmp->next->next = NULL;
	return (tmp->next);
}

char	*get_next_line(int fd)
{
	static t_list	*result;
	t_list			*putlist;
	char			*put_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	putlist = find_fd(&result, fd);
	if (!putlist)
		return (free_str(0, &result));
	putlist->line = get_next(putlist->fd, putlist->line);
	if (!putlist->line)
		return ((char *)ft_strlenfree(0, &result, putlist));
	put_line = ft_get_line(putlist->line);
	if (put_line != 0)
		putlist->line = keep_next_line(putlist->line);
	else
		return ((char *)ft_strlenfree(0, &result, putlist));
	return (put_line);
}
