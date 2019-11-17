/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/17 18:11:57 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/17 21:56:18 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static void		free_buffer(t_list **alst, int fd)
{
	t_list	*elem;
	t_list	*prev;

	if (alst == NULL)
		return ;
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
	ssize_t			endl;

	file = get_buffer(&buffers, fd);
	while (1)
	{
		size = read_file(fd, file);
		if (size < 1)
		{
			free_buffer(&buffers, fd);
			return (size);
		}
		endl = get_index(file->buf, '\n');
		if (endl < size)
		{
			*line = ft_strnjoin(*line, file->buf, endl);
			file->buf = ft_strndup(file->buf + endl + 1, size - endl - 1);
			return (1);
		}
		*line = ft_strnjoin(*line, file->buf, size);
		file->buf = NULL;
	}
}
