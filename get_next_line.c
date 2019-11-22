/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/22 16:02:24 by nschat        ########   odam.nl         */
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

static int		read_file(int fd, t_list *file)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t size;

	if (read(fd, buf, 0) < 0 || file == NULL)
		return (-1);
	if (file->buf != NULL)
	{
		size = get_index(file->buf, '\0');
		if (size == 0)
		{
			free(file->buf);
			file->buf = NULL;
		}
	}
	if (file->buf == NULL)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size <= 0)
			return (size);
		buf[size] = '\0';
		file->buf = ft_strndup(buf, size);
		if (file->buf == NULL)
			size = -1;
	}
	return (size);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	t_list			*file;
	ssize_t			size;
	ssize_t			newl;
	char			*out;

	file = get_buffer(&buffers, fd);
	out = NULL;
	while (1)
	{
		size = read_file(fd, file);
		if (size <= 0)
			break ;
		newl = get_index(file->buf, '\n');
		if (newl < size)
		{
			*line = ft_strnjoin(out, file->buf, newl);
			file->buf = ft_strndup(file->buf + newl + 1, size - newl - 1);
			return ((*line == NULL || file->buf == NULL) ? -1 : 1);
		}
		out = ft_strnjoin(out, file->buf, size);
		free(file->buf);
		if (out == NULL)
			return (-1);
		file->buf = NULL;
	}
	free_buffer(&buffers, fd);
	return (size);
}
