/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwokim <jinwokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:19:22 by jinwokim          #+#    #+#             */
/*   Updated: 2023/04/19 20:25:07 by jinwokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	int				fd;
	char			*line;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
char	*get_next(int fd, char *result);
char	*ft_get_line(char *result);
char	*keep_next_line(char *result);
size_t	ft_strlenfree(char *s, t_list **tmp, t_list *target);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*free_str(void *result, t_list **tmp);
t_list	*find_fd(t_list **result, int fd);
#endif