/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:28:07 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/06 14:35:39 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec(char *arg, char **envp);
static void	ft_close_fds(int fildes[2]);

void	ft_first_cmd(char *arg, char **envp, char *infile)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		fd;

	if (pipe(pipe_fd) == -1)
		ft_exit_message("Pipe failure");
	pid = fork();
	if (pid == -1)
		ft_exit_pipes("Fork failure", pipe_fd);
	else if (pid == 0)
	{
		fd = ft_open_file(infile, 0);
		if (fd == -1)
		{
			ft_close_fds(pipe_fd);
			ft_file_error(infile);
		}
		dup2(fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(fd);
		ft_close_fds(pipe_fd);
		ft_exec(arg, envp);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	ft_close_fds(pipe_fd);
}

pid_t	ft_final_cmd(char *arg, char **envp, char *outfile)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		ft_exit_message("Fork failure");
	else if (pid == 0)
	{
		fd = ft_open_file(outfile, 1);
		if (fd == -1)
			ft_file_error(outfile);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		ft_exec(arg, envp);
	}
	return (pid);
}

static void	ft_exec(char *arg, char **envp)
{
	char	*path;
	char	**argv;
	int		exit_code;

	argv = ft_split(arg, ' ');
	if (!argv)
		ft_exit_message("Failed to parse arguments");
	path = ft_test_paths(argv[0], envp);
	if (!path)
	{
		ft_free_str_arr(argv);
		ft_command_not_found(arg, envp);
	}
	ft_free((void **)&(argv[0]));
	argv[0] = path;
	execve(path, argv, envp);
	exit_code = ft_command_error(path);
	ft_free_str_arr(argv);
	exit(exit_code);
}

static void	ft_close_fds(int fildes[2])
{
	close(fildes[0]);
	close(fildes[1]);
}
