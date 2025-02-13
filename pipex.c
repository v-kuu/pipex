/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:32 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/13 15:11:41 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_wait(int commands, pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	pid_t	final_cmd;

	if (argc != 5)
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
