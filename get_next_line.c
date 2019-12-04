/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/12/04 14:49:13 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		free_recursive(t_list *lst, int fd)
{
	t_list	*node;

	if (lst->next->fd == fd)
	{
		node = lst->next;
		lst->next = lst->next->next;
		free(node->buf);
		free(node);
	}
	else
		free_recursive(lst->next, fd);
}

static void		free_buffer(t_list **alst, int fd)
{
	t_list	*node;

	node = *alst;
	if (node->fd == fd)
	{
		*alst = node->next;
		free(node->buf);
		free(node);
	}
	else
		free_recursive(node, fd);
}

static t_state	read_line(t_list *file, char **out)
{
	ssize_t	ret;
	size_t	i;

	if (file->size == 0)
	{
		ret = read(file->fd, file->buf, BUFFER_SIZE);
		if (ret == eof_read || ret == error)
			return (ret);
		file->buf[ret] = '\0';
		file->size = ret;
	}
	i = get_index(file->buf, '\n');
	*out = copy_buffer(*out, file->buf, i);
	if (*out == NULL)
		return (error);
	if (i < file->size)
	{
		file->size = file->size - i - 1;
		ft_strncpy(file->buf, file->buf + i + 1, file->size);
		return (line_read);
	}
	else
		file->size = 0;
	return (loop);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	t_list			*file;
	char			*out;
	t_state			state;

	file = get_buffer(&buffers, fd);
	if (file == NULL)
		return (error);
	out = NULL;
	state = loop;
	while (state == loop)
		state = read_line(file, &out);
	if (state == line_read)
		*line = out;
	if (state == eof_read)
	{
		*line = copy_buffer(out, "", 0);
		free_buffer(&buffers, fd);
		if (*line == NULL)
			return (error);
	}
	if (state == error)
		free_buffer(&buffers, fd);
	return (state);
}
