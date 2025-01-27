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

static void	*ft_exec(int *files, t_cmd command);

int	main(int argc, char **argv, char **envp)
{
	int		*files;
	t_cmd	*commands;

	if (argc < 5)
		return (EXIT_FAILURE);
	files = ft_check_files(argc, argv);
	if (!files)
		return (EXIT_FAILURE);
	commands = ft_calloc((argc - 3), sizeof(t_cmd));
	if (!commands)
		return (EXIT_FAILURE);
	commands = ft_parse_commands((argc - 3), &argv[2], envp, commands);
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
}

static void	*ft_exec(int *files, t_cmd command)
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
