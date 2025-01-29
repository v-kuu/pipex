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

static void	ft_exec(int files[2], t_cmd *commands, char **envp, int count);

int	main(int argc, char **argv, char **envp)
{
	int		files[2];
	t_cmd	*commands;

	if (argc < 5)
		return (EXIT_FAILURE);
	ft_check_files(argc, argv, files);
	commands = ft_calloc((argc - 3), sizeof(t_cmd));
	if (!commands)
		return (EXIT_FAILURE);
	commands = ft_parse_cmds((argc - 3), &argv[2], envp, commands);
	if (!commands)
	{
		if (files[0] != 1)
			close(files[0]);
		close(files[1]);
		return (EXIT_FAILURE);
	}
	ft_exec(files, commands, envp, (argc -3));
}

static void	ft_exec(int files[2], t_cmd *commands, char **envp, int count)
{
	int		index;
	int		fildes[2];
	pid_t	pid;

	fildes[0] = files[0];
	fildes[1] = 1;
	index = -1;
	while (++index < count)
	{
		pipe(fildes);
		pid = fork();
		if (pid == -1)
			ft_exit("Fork failure", commands, count);
		if (pid == 0)
		{
			dup2(fildes[0], STDIN_FILENO);
			execve(commands[index].path, commands[index].args, envp);
		}
		else
		{
			wait(NULL);
			fildes[0] = 0;
			if (index == count - 1)
				fildes[1] = files[1];
		}
	}
}
