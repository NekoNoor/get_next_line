/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:04:14 by nschat        #+#    #+#                 */
/*   Updated: 2019/12/06 22:23:22 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf_list	*get_buffer(t_buf_list **alst, int fd)
{
	t_buf_list	*node;
	t_buf_list	*new;

	node = *alst;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	new = (t_buf_list *)malloc(sizeof(t_buf_list));
	if (new == NULL)
		return (NULL);
	new->content = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (new->content == NULL)
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

size_t		get_index(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

char		*ft_strncpy(char *dst, const char *src, size_t n)
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

char		*copy_buffer(char *old, char *buf_content, size_t n)
{
	char	*new;
	size_t	len;

	if (old == NULL)
	{
		new = (char *)malloc(sizeof(char) * (n + 1));
		if (new == NULL)
			return (NULL);
		ft_strncpy(new, buf_content, n);
	}
	else
	{
		len = get_index(old, '\0');
		new = (char *)malloc(sizeof(char) * (len + n + 1));
		if (new == NULL)
			return (NULL);
		ft_strncpy(new, old, len);
		free(old);
		ft_strncpy(new + len, buf_content, n);
	}
	return (new);
}
