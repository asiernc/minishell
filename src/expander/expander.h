/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simarcha <simarcha@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:44:21 by simarcha          #+#    #+#             */
/*   Updated: 2024/06/20 18:37:17 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_expansor
{
	char	*final_line;
	int		i;
	int		lead;
	int		start;
	char	*substring;
	char	*tmp;
	char	*expansion_line;
}	t_expansor;

void	lead_is_zero_helper(char *str, t_expansor *expansion);
//void	lead_is_zero(t_mini *mini, char *str, t_expansor *expansion);
void	lead_is_zero(t_mini *mini, char *str, t_expansor *expansion,
					t_var g_var);
void	lead_is_one(t_mini *mini, char *str, t_expansor *expansion);
void	lead_is_two_helper(char *str, t_expansor *expansion);
//void	lead_is_two(t_mini *mini, char *str, t_expansor *expansion);
void	lead_is_two(t_mini *mini, char *str, t_expansor *expansion, t_var g_var);