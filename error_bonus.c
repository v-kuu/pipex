/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:10:51 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/13 15:58:52 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_file_error(char *filename)
{
	char	*full;
	int		file_len;

	file_len = ft_strlen(filename);
	full = ft_calloc((file_len + 8), sizeof(char));
	if (!full)
		ft_exit_message("Failed to print error message");
	ft_strlcat(full, "pipex: ", (file_len + 8));
	ft_strlcat(full, filename, (file_len + 8));
	perror(full);
	ft_free((void **)&full);
	exit(EXIT_FAILURE);
}

void	ft_is_command_directory(char *command, char **argv)
{
	char	*full;
	int		cmd_len;

	if (!command || !argv)
		return ;
	if (open(command, O_DIRECTORY) == -1)
		return ;
	ft_free_str_arr(argv);
	cmd_len = ft_strlen(command);
	full = ft_calloc(25 + cmd_len, sizeof(char));
	if (!full)
		ft_exit_message("Failed to pring error message");
	ft_strlcat(full, "pipex: ", (cmd_len + 25));
	ft_strlcat(full, command, (cmd_len + 25));
	ft_strlcat(full, ": Is a directory\n", (cmd_len + 25));
	ft_putstr_fd(full, 2);
	ft_free((void **)&full);
	ft_free((void **)&command);
	exit(126);
}
