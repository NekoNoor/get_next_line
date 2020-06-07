/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nschat <nschat@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 21:27:00 by nschat        #+#    #+#                 */
/*   Updated: 2020/05/31 22:02:27 by nschat        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	char	*line;
	int		fd[ac - 1];
	int 	ret;
	int		i;

	i = 1;
	while (i < ac)
	{
		fd[i - 1] = open(av[i], O_RDONLY);
		i++;
	}
	ret = 1;
	line = NULL;
	while (ret == 1)
	{
		i = 1;
		while (i < ac)
		{
			ret = get_next_line(fd[i - 1], &line);
			printf("fd: %i, ret: %i, line: \"%s\"\n", fd[i - 1], ret, line);
			free(line);
			i++;
		}
	}
	i = 1;
	while (i < ac)
	{
		close(fd[i - 1]);
		i++;
	}
	return (0);
}
