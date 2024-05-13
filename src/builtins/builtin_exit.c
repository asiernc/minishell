/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:08:54 by anovio-c          #+#    #+#             */
/*   Updated: 2024/05/13 18:06:21 by simarcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//we don't need a function for this
int	builtin_exit(void)
{
	return (exit(0), 0);//you have to go out with the exit status!
	//exit(EXIT_STATUS);
}
