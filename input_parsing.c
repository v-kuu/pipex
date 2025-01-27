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

static int	ft_open_file(char *file, int mode);

int	*ft_check_files(int argc, char **argv)
{
	int	*files;

	files[0] = ft_open_file(argv[1], 0);
	if (files[0] < 0)
		return (NULL);
	files[1] = ft_open_file(argv[argc - 2], 1);
	if (files[1] < 0)
	{
		if (files[0] != 1)
			close(files[0]);
		return (NULL);
	}
	return (files);
}

static int	ft_open_file(char *file, int mode)
{
	if (mode == 0 && ft_strncmp(file, "<<", 2) == 0)
		return (1);
	else if (mode == 0 && access(file, R_OK) != -1)
		return (open(file, O_RDONLY));
	else if (mode == 1 && access(file, W_OK) != -1)
		return (open(file, O_WRONLY | O_CREAT, 0644));
	else
		return (-1);
}

char	***ft_parse_commands(int argc, char **argv, char **envp)
{
	char	***commands;


	return (commands);
}
