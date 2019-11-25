/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:30 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/24 19:45:32 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_list
{
	char			*buf;
	ssize_t			size;
	int				fd;
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);

ssize_t			get_newl(char *s, ssize_t len);
size_t			ft_strlen(char *s);
void			*ft_memmove(void *dst, const void *src, size_t n);
char			*ft_strncpy(char *dst, char *src, size_t n);

#endif
