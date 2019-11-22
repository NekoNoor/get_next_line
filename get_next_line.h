/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:30 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/22 16:02:41 by nschat        ########   odam.nl         */
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
	int				fd;
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);

ssize_t			get_index(char *s, char c);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strndup(char *s1, size_t n);
char			*ft_strnjoin(char *s1, char *s2, size_t n);

#endif
