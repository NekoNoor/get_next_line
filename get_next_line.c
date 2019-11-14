/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:10 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/14 20:46:45 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //

int	get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE];
	static char	saved[BUFFER_SIZE + 1];
	ssize_t 	size;
	ssize_t 	endl;
	ssize_t		bytes_read;

	bytes_read = 0;
	size = 1;
	while (size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || size == 0)
			break ;
		endl = check_endl(buf, size);
		if (endl < size)
		{
			*line = buf_cat(*line, buf, endl, bytes_read);
			ft_memcpy(saved, buf + endl + 1, size - endl - 1);
			saved[size - endl] = '\0';
			return (1);
		}
		*line = buf_cat(*line, buf, size, bytes_read);
		bytes_read += size;
	}
	return (size);
}
