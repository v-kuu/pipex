/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/23 13:28:28 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_check_args(int *argc, char **argv, t_data *data)
{
	int	index;

	index = 1;
	// if argv[1] != infile / heredoc
	// BOOM
	// if argv[argc - 1] != outfile
	// BOOM
	while (argv[index])
}
