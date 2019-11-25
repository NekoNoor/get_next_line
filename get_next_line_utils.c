/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:04:14 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/25 20:30:55 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*get_buffer(t_list **alst, int fd)
{
	t_list	*node;
	t_list	*new;

	node = *alst;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (new->buf == NULL)
	{
		free(new);
		return (NULL);
	}
	new->size = 0;
	new->fd = fd;
	new->next = *alst;
	*alst = new;
	return (new);
}

size_t	get_index(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*copy_buffer(char *old, t_list *file, size_t newl)
{
	char	*new;
	size_t	len;

	if (old == NULL)
	{
		new = (char *)malloc(sizeof(char) * (newl + 1));
		if (new == NULL)
			return (NULL);
		ft_strncpy(new, file->buf, newl);
	}
	else
	{
		len = get_index(old, '\0');
		new = (char *)malloc(sizeof(char) * (len + newl + 1));
		if (new == NULL)
			return (NULL);
		ft_strncpy(new, old, len);
		free(old);
		ft_strncpy(new + len, file->buf, newl);
	}
	return (new);
}
