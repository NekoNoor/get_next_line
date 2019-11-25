/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/25 19:04:01 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static t_list	*buffers;
	t_list			*file;
	char			*out;
	ssize_t			ret;
	size_t			i;

	file = get_buffer(&buffers, fd);
	if (file == NULL)
		return (-1);
	out = NULL;
	while (1)
	{
		if (file->size == 0)
		{
			ret = read(fd, file->buf, BUFFER_SIZE);
			if (ret <= 0)
				break ;
			file->buf[ret] = '\0';
			file->size = ret;
		}
		else
		{
			i = get_index(file->buf, '\n');
			out = copy_buffer(out, file, i);
			if (out == NULL)
			{
				ret = -1;
				break ;
			}
			if (i < file->size)
			{
				ft_strncpy(file->buf, file->buf + i + 1, file->size - i - 1);
				file->size = file->size - i - 1;
				*line = out;
				return (1);
			}
			else
				file->size = 0;
		}
	}
	free_buffer(&buffers, fd);
	return (ret);
}
