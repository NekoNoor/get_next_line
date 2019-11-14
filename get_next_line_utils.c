/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 18:04:14 by nschat        #+#    #+#                 */
/*   Updated: 2019/11/14 20:37:59 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	check_endl(char *buf, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while (i < size)
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_uc;
	unsigned const char	*src_ucc;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_uc = (unsigned char *)dst;
	src_ucc = (unsigned const char *)src;
	i = 0;
	while (i < n)
	{
		dst_uc[i] = src_ucc[i];
		i++;
	}
	return (dst);
}

char	*buf_cat(char *cat, char *buf, ssize_t size, ssize_t read)
{
	char	*new;

	if (cat == NULL)
	{
		new = (char *)malloc(sizeof(char) * (size + 1));
		if (new == NULL)
			return (NULL);
		ft_memcpy(new, buf, size);
		new[size] = '\0';
		return (new);
	}
	new = (char *)malloc(sizeof(char) * (size + read + 1));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, cat, read);
	free(cat);
	ft_memcpy(new + read, buf, size);
	new[size + read] = '\0';
	return (new);
}
