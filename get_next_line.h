/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:03:30 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/26 12:28:34 by nschat        ########   odam.nl         */
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

enum			e_state
{
	error = -1,
	eof_read = 0,
	line_read = 1,
	loop = 2
};

typedef struct	s_list
{
	char			*buf;
	size_t			size;
	int				fd;
	struct s_list	*next;
}				t_list;

int				get_next_line(int fd, char **line);

t_list			*get_buffer(t_list **alst, int fd);
size_t			get_index(char *s, char c);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*copy_buffer(char *old, t_list *file, size_t newl);

#endif
