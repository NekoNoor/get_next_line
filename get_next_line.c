/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/12/06 22:22:59 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void		free_recursive(t_buf_list *lst, int fd)
{
	t_buf_list	*node;

	if (lst->next->fd == fd)
	{
		node = lst->next;
		lst->next = lst->next->next;
		free(node->content);
		free(node);
	}
	else
		free_recursive(lst->next, fd);
}

static void		free_buffer(t_buf_list **alst, int fd)
{
	t_buf_list	*node;

	node = *alst;
	if (node->fd == fd)
	{
		*alst = node->next;
		free(node->content);
		free(node);
	}
	else
		free_recursive(node, fd);
}

static t_state	read_line(t_buf_list *buf, char **out)
{
	ssize_t	ret;
	size_t	i;

	if (buf->size == 0)
	{
		ret = read(buf->fd, buf->content, BUFFER_SIZE);
		if (ret == eof_read || ret == error)
			return (ret);
		buf->content[ret] = '\0';
		buf->size = ret;
	}
	i = get_index(buf->content, '\n');
	*out = copy_buffer(*out, buf->content, i);
	if (*out == NULL)
		return (error);
	if (i < buf->size)
	{
		buf->size = buf->size - i - 1;
		ft_strncpy(buf->content, buf->content + i + 1, buf->size);
		return (line_read);
	}
	else
		buf->size = 0;
	return (loop);
}

int				get_next_line(int fd, char **line)
{
	static t_buf_list	*buf_list;
	t_buf_list			*buf;
	char				*out;
	t_state				state;

	buf = get_buffer(&buf_list, fd);
	if (buf == NULL)
		return (error);
	out = NULL;
	state = loop;
	while (state == loop)
		state = read_line(buf, &out);
	if (state == line_read)
		*line = out;
	if (state == eof_read)
	{
		*line = copy_buffer(out, "", 0);
		free_buffer(&buf_list, fd);
		if (*line == NULL)
			return (error);
	}
	if (state == error)
		free_buffer(&buf_list, fd);
	return (state);
}
