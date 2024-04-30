/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:11:30 by simarcha          #+#    #+#             */
/*   Updated: 2024/04/30 19:06:09 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct	s_builtin
{
	char				*key;//the name of the variable in env
	char				*value;
	int					index;
//	int					checker;//to check if the builtin is ENV or EXPORT
	struct s_builtin	*next;
}				t_builtin;//for ENV and EXPORT builtins

t_builtin	*ft_lstnew_builtin(char *str, int i);
void		ft_lstadd_back_builtin(t_builtin **lst, t_builtin *new);
void		print_list(t_builtin **lst_env);
void		ft_lstclear_builtin(t_builtin **lst);

//for each line of our env, we want to get the characters before the '='
//this will be the content of the 'key' variable in our structure
char	*get_key_from_env(char *str)//to free once used
{
	int		i;
	int		len_str;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	len_str = i;
	result = malloc((len_str + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len_str)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

//for each line of our env, we want to get the characters after the '='
//this will be the content of the 'value' variable in our structure
char	*get_value_from_env(char *str)//to free once used
{
	int		i;
	int		j;
	int		len_str;
	char	*result;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	i++;
	j = i;
	while (str[i])
		i++;
	len_str = i - j;
	result = malloc((len_str + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (j < (int)ft_strlen(str))
		result[i++] = str[j++];
	result[j] = '\0';
	return (result);
}

t_builtin	*create_builtin_lst(char **env)//to free once used
{
	t_builtin	*new_node;
	t_builtin	*lst_env;
	int			i;

	i = 0;
	lst_env = NULL;
	while (env[i])
	{
		new_node = ft_lstnew_builtin(env[i], i);
		if (!new_node)
			return (NULL);
		ft_lstadd_back_builtin(&lst_env, new_node);
		i++;
	}
	return (lst_env);
}

void	builtin_env(char **env)
{
	t_builtin	*lst_env;
	t_builtin	*tmp;

	lst_env = create_builtin_lst(env);
	if (!lst_env)
		perror("error creating the list for the env");
	tmp = lst_env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	ft_lstclear_builtin(&lst_env);
}

/*int	main(int argc, char **argv, char **env)
{
	builtin_export(env);
	argc = 0;
	argv[0] = "./a.out";
	printf("%lu\n", sizeof(t_builtin));
	return (0);
}
*/
