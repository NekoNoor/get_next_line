/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/25 20:22:19 by nschat        ########   odam.nl         */
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
	if ((*alst)->fd == fd)
	{
		free((*alst)->buf);
		free(*alst);
		*alst = NULL;
	}
	else
		free_recursive(*alst, fd);
}

static ssize_t	read_line(t_list *file, char **out)
{
	ssize_t	ret;
	size_t	i;

	if (file->size == 0)
	{
		ret = read(file->fd, file->buf, BUFFER_SIZE);
		if (ret == EOF_READ || ret == ERROR)
			return (ret);
		file->buf[ret] = '\0';
		file->size = ret;
		return (CONTINUE);
	}
	i = get_index(file->buf, '\n');
	*out = copy_buffer(*out, file, i);
	if (*out == NULL)
		return (ERROR);
	if (i < file->size)
	{
		ft_strncpy(file->buf, file->buf + i + 1, file->size - i - 1);
		file->size = file->size - i - 1;
		return (LINE_READ);
	}
	else
		file->size = 0;
	return (CONTINUE);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	t_list			*file;
	char			*out;
	ssize_t			ret;

	file = get_buffer(&buffers, fd);
	if (file == NULL)
		return (ERROR);
	out = NULL;
	ret = CONTINUE;
	while (ret == CONTINUE)
		ret = read_line(file, &out);
	if (ret == LINE_READ)
		*line = out;
	else
		free_buffer(&buffers, fd);
	return (ret);
}
