/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_tests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:51:16 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/25 18:11:38 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup(env[++i]);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	printf("str = %s\n", str);
	return (0);
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cd(char *path) {
    if (chdir(path) == -1) {
        perror("cd");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (cd(argv[1]) == EXIT_FAILURE) {
        fprintf(stderr, "Failed to change directory.\n");
        return EXIT_FAILURE;
    }

    printf("Changed directory to: %s\n", argv[1]);
    return EXIT_SUCCESS;
}

