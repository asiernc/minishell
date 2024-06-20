/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:56:28 by anovio-c          #+#    #+#             */
/*   Updated: 2024/06/20 17:34:32 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	if (!str)
		return (0);
	res = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	res *= sign;
	return (res);
}
/*
#include <stdio.h>
#include <stdlib.h>

int     ft_isdigit(int c)
{
        if (c >= '0' && c <= '9')
                return (1);
        return (0);
}

int	main(void)
{
	char	str[8] = "  --234";
	int	res = ft_atoi(str);

	printf("  --234: %d\n", ft_atoi(str));
	printf("  --234: %d\n", atoi(str));

	//printf("El string es: %s, y su conversion a numerico es: %d\n", str, res);
	return (0);
}*/
/*#include <stdio.h>
int	main(void)
{
	char	s[5] = "";
	int		result;
	
	result = ft_atoi(s);
	printf("result = %i\n", result);
	return (0);
}*/

