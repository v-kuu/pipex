/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:32 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/22 14:21:30 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	*ft_exec(int *files, char **command);

int	main(int argc, char **argv, char **envp)
{
	int		*files;
	char	***commands;

	if (argc < 5)
		return (EXIT_FAILURE);
	files = ft_check_files(argc, argv);
	if (!files)
		return (EXIT_FAILURE);
	commands = ft_parse_commands(argc, argv, envp);
	if (!commands)
	{
		if (files[0] != 1)
			close(files[0]);
		close(files[1]);
		return (EXIT_FAILURE);
	}
	while (commands)
	{
		ft_exec(files, *commands);
		commands++;
	}
	// cleanup
}

static void	*ft_exec(int *files, char **command)
{
	// pipe
	// fork
	// if (child)
	// {
	//		dup2
	//		execve
	//	}
	//	else
	//	{
	//		close
	//	}
}
