/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/22 15:05:22 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_buffer(t_list **alst, int fd)
{
	t_list	*elem;
	t_list	*new;

	elem = *alst;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->buf = NULL;
	new->fd = fd;
	new->next = *alst;
	*alst = new;
	return (new);
}

static void		free_buffer(t_list **alst, int fd)
{
	t_list	*elem;
	t_list	*prev;

	elem = *alst;
	prev = NULL;
	while (elem)
	{
		if (elem->fd == fd)
		{
			if (prev == NULL)
				*alst = elem->next;
			else
				prev->next = elem->next;
			free(elem->buf);
			free(elem);
		}
		prev = elem;
		elem = elem->next;
	}
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	t_list			*file;
	ssize_t			size;
	ssize_t			newl;
	char			*out;

	file = get_buffer(&buffers, fd);
	size = 1;
	out = NULL;
	while (size > 0)
	{
		size = read_file(fd, file);
		if (size <= 0)
			break ;
		newl = get_index(file->buf, '\n');
		if (newl < size)
		{
			*line = ft_strnjoin(out, file->buf, newl);
			file->buf = ft_strndup(file->buf + newl + 1, size - newl - 1);
			if (*line == NULL || file->buf == NULL)
				return (-1);
			return (1);
		}
		out = ft_strnjoin(out, file->buf, size);
		if (out == NULL)
			return (-1);
		file->buf = NULL;
	}
	free_buffer(&buffers, fd);
	return (size);
}
