/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:04:14 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/24 19:45:32 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_newl(char *s, ssize_t len)
{
	ssize_t	i;

	i = 0;
	while (i < len)
	{
		if (s[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned const char	*src_ucc;
	unsigned char 		*dst_uc;
	size_t	i;

	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			dst_uc[i] = src_ucc[i];
			i++;
		}
	}
	else
	{
		while (n)
		{
			n--;
			dst_uc[n] = src_ucc[n];
		}
	}
	return (dst);
}

char	*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t	len;

	len = ft_strlen(src);
	if (len < n)
		n = len;
	ft_memmove(dst, src, n);
	dst[n] = '\0';
	return (dst);
}
