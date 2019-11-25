/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/24 19:45:32 by nschat        ########   odam.nl         */
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
	new->buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
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

static int		concat_buffer(char **output, t_list *file)
{
	char	*new;
	size_t	len;
	size_t	newl;

	if (*output != NULL)
		len = ft_strlen(*output);
	else
		len = 0;
	new = (char *)malloc(sizeof(char) * (len + file->size + 1));
	if (new == NULL)
		return (-1);
	ft_strncpy(new, *output, len);
	free(*output);
	newl = get_newl(file->buf, file->size);
	ft_strncpy(new + len, file->buf, newl);
	if (new < file->size)
	{
		ft_strncpy(file->buf, file->buf + newl + 1, file->size - newl - 1);
		file->size = file->size - newl - 1;
		return (1);
	}
	return (0);
}

static ssize_t	read_file(t_list *file)
{
	ssize_t	size;

	if (file->size == 0)
	{
		size = read(file->fd, file->buf, BUFFER_SIZE);
		file->size = size;
	}
	else
		size = file->size;
	return (size);
}

int				get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	char			*output;
	t_list			*file;
	sret_t			ret;
	sret_t			newl;

	file = get_buffer(&buffers, fd);
	if (file == NULL)
		return (-1);
	output = NULL;
	while (ret == 1)
	{
		ret = read_file(file);
		if (ret <= 0)
			break ;
		ret = concat_buffer(&output, file);
		if (ret == -1 || ret == 1)
			break ;
	}
	if (ret <= 0)
		free_buffer(&buffers, fd);
	else
		*line = output;
	return (ret);
}
