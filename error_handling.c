/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:23:16 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/23 13:24:56 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(const char *string, t_cmd *commands)
{
	ft_free_commands(commands);
	perror(string);
	exit(EXIT_FAILURE);
}

void	*ft_free_commands(t_cmd *commands)
{
	t_cmd	*eraser;

	eraser = commands;
	while (eraser)
	{
		free(eraser->path);
		ft_free_str_arr(eraser->args);
		eraser++;
	}
	free(commands);
	return (NULL);
}
