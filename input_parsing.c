/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/23 13:47:13 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_check_infile(char *file);

int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	index;
	int	ret;

	ret = ft_check_infile(argv[1]);
	if (!ret)
		return (0);
	// if argv[argc - 1] != outfile
	// BOOM
	index = 2;
	data->infile = open(argv[1], O_RDONLY);
	data->outfile = open(argv[argc - 1], O_WRONLY);
	while (argv[index] && index < (argc - 1))
	{
		if (argv[index] != cmd)
			// BOOM
	}
}

static int	ft_check_infile(char *file)
{
	if (ft_strncmp(file, "<<", 2) == 0)
		return (2);
	else if (access(file, R_OK) < 0)
		return (0);
	else
		return (1);
}
