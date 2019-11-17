/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/17 18:11:21 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/17 18:14:17 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
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
int				read_file(int fd, t_list *file);

#endif
