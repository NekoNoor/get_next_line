/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/16 19:15:28 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*new_buffer(char *buf, int fd)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->buf = buf;
	new->fd = fd;
	new->next = NULL;
	return (new);
}

static void		add_buffer(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

static t_list	*get_buffer(t_list **alst, int fd)
{
	t_list	*elem;

	if (alst == NULL)
		return (NULL);
	elem = *alst;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	add_buffer(alst, new_buffer(NULL, fd));
	return (*alst);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	char			buf[BUFFER_SIZE + 1];
	t_list			*file;
	ssize_t			size;
	ssize_t			endl;

	if (fd < 0)
		return (-1);
	file = get_buffer(&buffers, fd);
	while (1)
	{
		if (file->buf == NULL)
		{
			size = read(fd, buf, BUFFER_SIZE);
			if (size == -1 || size == 0)
				return (size);
			buf[size] = '\0';
			file->buf = ft_strndup(buf, size);
		}
		endl = get_index(file->buf, '\n');
		size = get_index(file->buf, '\0');
		if (endl < size)
		{
			*line = buf_cat(*line, file->buf, endl);
			file->buf = ft_strndup(file->buf + endl + 1, size - endl - 1);
			return (1);
		}
		*line = buf_cat(*line, file->buf, size);
		file->buf = NULL;
	}
}
