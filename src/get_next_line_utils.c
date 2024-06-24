/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:12:56 by anovio-c          #+#    #+#             */
/*   Updated: 2024/01/31 14:51:30 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *str, size_t len)
{
	char	*cpy;
	size_t	i;

	i = 0;
	cpy = (char *)str;
	while (i < len)
		cpy[i++] = '\0';
}

void	*ft_calloc(size_t len, size_t size)
{
	char	*dest;

	dest = (char *)malloc(len * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, (len * size));
	return (dest);
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buff, char *content)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	if (!buff || !content)
		return (NULL);
	len = ft_strlen(buff) + ft_strlen(content);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (buff[i] != '\0')
	{
		result[i] = buff[i];
		i++;
	}
	j = 0;
	while (content[j] != '\0')
		result[i++] = content[j++];
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	else
		return (NULL);
}
