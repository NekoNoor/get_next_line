/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:04:14 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/16 18:57:03 by nschat        ########   odam.nl         */
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
	if (len < n)
		n = len;
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (s2 == NULL)
		return (NULL);
	return (ft_strncpy(s2, s1, n));
}

char	*buf_cat(char *cat, char *buf, size_t n)
{
	char	*new;
	size_t	catlen;
	size_t	buflen;

	buflen = get_index(buf, '\0');
	if (buflen < n)
		n = buflen;
	if (cat == NULL)
		return (ft_strndup(buf, n));
	catlen = get_index(cat, '\0');
	if (n == 0)
		return (ft_strndup(cat, catlen));
	new = (char *)malloc(sizeof(char) * (catlen + n + 1));
	if (new == NULL)
		return (NULL);
	ft_strncpy(new, cat, catlen);
	free(cat);
	ft_strncpy(new + catlen, buf, n);
	free(buf);
	return (new);
}
