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

void	ft_first_cmd(char *arg, char **envp, char *infile, int heredoc)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		fd;

	if (pipe(pipe_fd) == -1)
		perror("Pipe failure");
	pid = fork();
	if (pid == -1)
		perror("Fork failure");
	else if (pid == 0)
	{
		fd = ft_open_file(infile, heredoc);
		if (fd == -1)
		{
			ft_close_fds(pipe_fd);
			exit(EXIT_FAILURE);
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

void	ft_mid_cmd(char *arg, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror("Pipe failure");
	pid = fork();
	if (pid == -1)
		perror("Fork failure");
	else if (pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		ft_exec(arg, envp);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
}

pid_t	ft_final_cmd(char *arg, char **envp, char *outfile, int heredoc)
{
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid == -1)
		perror("Fork failure");
	else if (pid == 0)
	{
		fd = ft_open_file(outfile, heredoc + 2);
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

	argv = ft_split(arg, ' ');
	if (!argv)
	{
		perror("Failed to parse arguments");
		exit(EXIT_FAILURE);
	}
	path = ft_test_paths(argv[0], envp);
	execve(path, argv, envp);
	perror("Execve failure");
	exit(EXIT_FAILURE);
}

static void	ft_close_fds(int fildes[2])
{
	close(fildes[0]);
	close(fildes[1]);
}
