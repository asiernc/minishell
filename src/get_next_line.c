/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:12:27 by anovio-c          #+#    #+#             */
/*   Updated: 2024/02/03 16:20:44 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_read_line(char *str)
{
	size_t	i;
	char	*new_line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] && str[i] == '\n')
		i++;
	new_line = ft_calloc((i + 1), sizeof(char));
	if (!new_line)
		return (free(str), NULL);
	i = 0;
	while (*(str + i) && *(str + i) != '\n')
	{
		*(new_line + i) = *(str + i);
		i++;
	}
	if (*(str + i) && *(str + i) == '\n')
		new_line[i++] = '\n';
	return (new_line);
}

char	*ft_substr(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buffer = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	i++;
	while (*(buffer + i))
		*(new_buffer + j++) = *(buffer + i++);
	free(buffer);
	return (new_buffer);
}

static char	*ft_free_join(char *buffer, char *buff)
{
	char	*result;

	result = ft_strjoin(buffer, buff);
	free(buffer);
	return (result);
}

char	*ft_read_file(int fd, char *buffer)
{
	char	*buff;
	int		bytes;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buff)
		return (free(buffer), NULL);
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		buff[bytes] = '\0';
		buffer = ft_free_join(buffer, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*new_line;
	static char	*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	new_line = ft_read_line(buffer);
	buffer = ft_substr(buffer);
	return (new_line);
}
/*
#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*res;

	fd = open("only_nl.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("RES: %s", res);
	res = get_next_line(fd);
	printf("RES: %s", res);
	res = get_next_line(fd);
	printf("RES: %s", res);
	res = get_next_line(fd);
	printf("RES: %s", res);
	free(res);
	return (0);
}*/
