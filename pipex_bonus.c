/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:32 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:23 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_wait(int commands, pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	int		index;
	int		heredoc;
	pid_t	final_cmd;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_putendl_fd(
			"Usage: ./pipex <infile/here_doc EOF> <cmd1>...<cmdn> outfile>", 2);
		exit(EXIT_FAILURE);
	}
	heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		heredoc = 1;
	index = 2 + heredoc;
	ft_first_cmd(argv[index++], envp, argv[1 + heredoc], heredoc);
	while (index < argc - 2)
		ft_mid_cmd(argv[index++], envp);
	final_cmd = ft_final_cmd(argv[argc - 2], envp, argv[argc - 1], heredoc);
	ft_wait((argc - 3 - heredoc), final_cmd);
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
