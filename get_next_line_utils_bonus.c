/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils_bonus.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/17 18:11:48 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/17 18:11:49 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_index(char *s, char c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (src[i] == '\0')
			break ;
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(char *s1, size_t n)
{
	char	*s2;
	size_t	len;

	len = get_index(s1, '\0');
	if (n == 0 || len == 0 || *s1 == '\0')
		return (NULL);
	if (len < n)
		n = len;
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (s2 == NULL)
		return (NULL);
	return (ft_strncpy(s2, s1, n));
}

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*new;
	size_t	s1len;
	size_t	s2len;

	s2len = get_index(s2, '\0');
	if (s2len < n)
		n = s2len;
	if (s1 == NULL)
		return (ft_strndup(s2, n));
	s1len = get_index(s1, '\0');
	if (n == 0)
		return (ft_strndup(s1, s1len));
	new = (char *)malloc(sizeof(char) * (s1len + n + 1));
	if (new == NULL)
		return (NULL);
	ft_strncpy(new, s1, s1len);
	free(s1);
	ft_strncpy(new + s1len, s2, n);
	free(s2);
	return (new);
}

int		read_file(int fd, t_list *file)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t size;

	if (read(fd, buf, 0) < 0)
		return (-1);
	if (file->buf == NULL)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1 || size == 0)
			return (size);
		buf[size] = '\0';
		file->buf = ft_strndup(buf, size);
		if (file->buf == NULL)
			size = -1;
	}
	else
		size = get_index(file->buf, '\0');
	return (size);
}
