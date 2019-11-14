/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:30 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/14 20:38:11 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
ssize_t	check_endl(char *str, ssize_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*buf_cat(char *cat, char *buf, ssize_t size, ssize_t read);

#endif
