/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:02:58 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/22 20:39:27 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

//in this file, I want to retrieve the first command
//let's suppose that we have the line that the user inputs

//we will check every character until the first operator.
//We will return the index of where it is
//if we didn't found it, we return -1.
int	check_operator(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (i);
		i++;
	}
	return (-1);
}

//once done, we have a string with the beginning of the line until the first 
//operator
//Now, if there is isspace characters at the beginning or at the end, we want to
//erase them.
int	main(int argc, char **argv)
{
	int		i;
	int		j;
	int		index;
	char	*str;

	i = 0;
	index = 0;
	if (argc == 2)
	{
		j = 0;
		while (argv[1][j])
		{
			index = check_operator(argv[1]);
			if (index != -1)
			{
				printf("index = %i\n", index);
				break ;
			}
			j++;
		}
		str = ft_substr(argv[1], 0, index);
		printf("after substr, str = %s\n", str);
		str = ft_strtrim(str, " ");//space	
		str = ft_strtrim(str, "	 ");//tab
		printf("after strtrim, str = %s\n", str);
		printf("the first command is: __%s__\n", str);
		free(str);
	}
	else
		perror("write only 2 argv\n");
	return (0);
}
