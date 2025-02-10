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

static void		ft_exit(int commands, pid_t last_pid);

int	main(int argc, char **argv, char **envp)
{
	int		index;
	int		heredoc;
	pid_t	final_cmd;

	if (argc < 5 || (ft_strncmp(argv[1], "here_doc", 8) == 0 && argc < 6))
	{
		ft_printf(
			"Usage: ./pipex <infile/here_doc DELIM> <cmd1>...<cmdn> outfile>");
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
	ft_exit((argc - 3 - heredoc), final_cmd);
}

static void	ft_exit(int commands, pid_t last_pid)
{
	int		status_code;
	int		exit_code;
	pid_t	current_pid;

	while (commands-- > 0)
	{
		current_pid = wait(&status_code);
		if (current_pid == last_pid && WIFEXITED(status_code))
			exit_code = WEXITSTATUS(status_code);
	}
	exit(exit_code);
}
