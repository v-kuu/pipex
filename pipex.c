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

static void	ft_pass_to_child(char *arg, char **envp);
static void	ft_exec(char *arg, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	index;
	int	files[2];

	if (argc < 5)
	{
		ft_printf("Usage: ./pipex <infile/here_doc> <cmd1>...<cmdn> outfile>");
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		index = 3;
		ft_open_files(argv[2], argv[argc - 1], files, true);
		dup2(files[0], STDIN_FILENO);
	}
	else
	{
		index = 2;
		ft_open_files(argv[1], argv[argc - 1], files, false);
		dup2(files[0], STDIN_FILENO);
	}
	while (index < argc - 2)
		ft_pass_to_child(argv[index++], envp);
	dup2(files[1], STDOUT_FILENO);
	ft_exec(argv[argc - 2], envp);
}

static void	ft_pass_to_child(char *arg, char **envp)
{
	pid_t	pid;
	int		fildes[2];

	if (pipe(fildes) == -1)
		perror("Pipe failure");
	pid = fork();
	if (pid == -1)
		perror("Fork failure");
	else if (pid == 0)
	{
		dup2(fildes[1], STDOUT_FILENO);
		close(fildes[0]);
		ft_exec(arg, envp);
	}
	else
	{
		dup2(fildes[0], STDIN_FILENO);
		close(fildes[1]);
		waitpid(pid, NULL, 0);
	}
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
	if (!path)
	{
		perror("Invalid command");
		exit(EXIT_FAILURE);
	}
	execve(path, argv, envp);
	perror("Execve failure");
}
