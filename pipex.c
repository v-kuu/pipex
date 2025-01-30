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
static void	ft_first_cmd(int fds[2], int temp[2], t_cmd *commands, char **envp);
static void	ft_last_cmd(int fds[2], int temp[2], t_cmd *commands, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int		files[2];
	t_cmd	*commands;

	if (argc < 5)
		return (EXIT_FAILURE);
	ft_check_files(argc, argv, files);
	commands = ft_calloc((argc - 2), sizeof(t_cmd));
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
	ft_free_commands(commands);
	exit(EXIT_SUCCESS);
}

static void	ft_exec(int files[2], t_cmd *commands, char **envp, int count)
{
	int		index;
	int		temp[2];
	pid_t	pid;

	if (pipe(temp) < 0)
		ft_exit("Pipe failure", commands);
	ft_first_cmd(files, temp, commands, envp);
	index = 0;
	while (++index < count - 1)
	{
		pid = fork();
		if (pid == -1)
			ft_exit("Fork failure", commands);
		if (pid == 0)
		{
			dup2(temp[0], STDIN_FILENO);
			close(temp[1]);
			close(files[0]);
			close(files[1]);
			execve(commands[index].path, commands[index].args, envp);
			ft_exit("Execve failure", commands);
		}
		dup2(temp[1], STDOUT_FILENO);
		close(temp[0]);
	}
	index = -1;
	ft_last_cmd(files, temp, commands, envp);;
	while (++index < count)
		wait(NULL);
	close(files[0]);
	close(files[1]);
}

static void	ft_first_cmd(int fds[2], int temp[2], t_cmd *commands, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit("Fork failure first cmd", commands);
	if (pid == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		dup2(temp[1], STDOUT_FILENO);
		close(temp[0]);
		execve(commands[0].path, commands[0].args, envp);
		ft_exit("Execve failure", commands);
	}
}

static void	ft_last_cmd(int fds[2], int temp[2], t_cmd *commands, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_exit("Fork failure last cmd", commands);
	if (pid == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		dup2(temp[0], STDIN_FILENO);
		close(temp[1]);
		execve(commands[1].path, commands[1].args, envp);
		ft_exit("Execve failure", commands);
	}
}
