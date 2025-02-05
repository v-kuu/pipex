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

static void		ft_pass_to_child(char *arg, char **envp);
static void		ft_exec(char *arg, char **envp);
static pid_t	ft_final_cmd(char *arg, char **envp);
static void		ft_exit(int commands, int files[2], pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	int		index;
	int		files[2];
	int		heredoc;
	pid_t	final_cmd;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_printf(
			"Usage: ./pipex <infile/here_doc DELIM> <cmd1>...<cmdn> outfile>");
		exit(EXIT_SUCCESS);
	}
	heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		heredoc = 1;
	ft_open_files(argv[1 + heredoc], argv[argc - 1], files, heredoc);
	dup2(files[0], STDIN_FILENO);
	index = 2 + heredoc;
	while (index < argc - 2)
		ft_pass_to_child(argv[index++], envp);
	dup2(files[1], STDOUT_FILENO);
	final_cmd = ft_final_cmd(argv[argc - 2], envp);
	ft_exit((argc - 3 - heredoc), files, final_cmd);
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
	execve(path, argv, envp);
	perror("Execve failure");
	exit(EXIT_FAILURE);
}

static pid_t	ft_final_cmd(char *arg, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Fork failure");
	else if (pid == 0)
		ft_exec(arg, envp);
	return (pid);
}

static void	ft_exit(int commands, int files[2], pid_t last_pid)
{
	int		status_code;
	int		exit_code;
	pid_t	current_pid;

	close(files[0]);
	close(files[1]);
	while (commands-- > 0)
	{
		current_pid = wait(&status_code);
		if (current_pid == last_pid && WIFEXITED(status_code))
			exit_code = WEXITSTATUS(status_code);
	}
	exit(exit_code);
}
