/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:32:12 by simarcha          #+#    #+#             */
/*   Updated: 2024/05/19 16:56:23 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	builtin_cd(char *path, char **env)
{

}*/

int main(void) 
{ 
    char s[100]; 
	char p[100] = "/Users/simarcha/commonCore/";
 
    printf("%s\n", getcwd(s, 100)); 
 
    chdir("/"); 
 
    printf("%s\n", getcwd(s, 100)); 
 
	chdir(p); 
 
    printf("%s\n", getcwd(s, 100)); 
    return 0; 
}

/*int	main(void)
{
	char	*path = "Users/simarcha/commonCore/";
	int		chdir_result;

	chdir_result = chdir(path);
	if (chdir_result == -1)
//		print_error("chdir function failed");
		printf("chdir_result == -1\n");
	printf("chdir result = %i\n", chdir_result);
//	printf("%s\n", path);
	return (0);
}*/

//cmd->str will contain the path
int	builtin_cd(t_mini *mini, t_cmd *cmd)
{
	t_builtin	*tmp;

	tmp = mini->env_list;
	if (cmd->str[1])
	{
		if (chdir(cmd->str[1]) == -1)
			return (print_error(mini, mini->lexer, 11), 1);//11 <=> CD_ERROR
		//do stuff
		return (0);
	}
	//you have to check what is your HOME variable in the env list
	//in that sense, if the user do "cd", it solely goes to the HOME path
	if (tmp)
	{
		while (ft_strcmp_simple(tmp->key, "HOME") != 0)
			tmp = tmp->next;
		if (chdir(tmp->value) == -1)
			return (print_error(mini, mini->lexer, 11), 1);//11 <=> CD_ERROR
		else
			return (0);
			
	}
	return ();
}