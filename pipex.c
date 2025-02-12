/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:32 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/06 14:35:50 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_wait(int commands, pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	pid_t	final_cmd;

	if (argc < 5)
	{
		ft_putstr_fd(
			"Usage: ./pipex <infile> <cmd1> <cmd2> outfile>\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_first_cmd(argv[2], envp, argv[1]);
	final_cmd = ft_final_cmd(argv[3], envp, argv[4]);
	ft_wait(2, final_cmd);
}

static void	ft_wait(int commands, pid_t last_pid)
{
	int		status_code;
	int		exit_code;
	pid_t	current_pid;

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	while (commands-- > 0)
	{
		current_pid = wait(&status_code);
		if (current_pid == last_pid && WIFEXITED(status_code))
			exit_code = WEXITSTATUS(status_code);
	}
	exit(exit_code);
}

void	ft_exit_message(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_exit_pipes(char *message, int fds[2])
{
	perror(message);
	close(fds[0]);
	close(fds[1]);
	exit(EXIT_FAILURE);
}

int	ft_command_error(char *command)
{
	char	*full;
	int		cmd_len;
	int		exit_code;

	if (access(command, F_OK))
		exit_code = 127;
	else
		exit_code = 126;
	cmd_len = ft_strlen(command);
	full = ft_calloc((cmd_len + 8), sizeof(char));
	if (!full)
		ft_exit_message("Failed to print error message");
	ft_strlcat(full, "pipex: ", (cmd_len + 8));
	ft_strlcat(full, command, (cmd_len + 8));
	perror(full);
	ft_free((void **)&full);
	return (exit_code);
}
