/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:10:51 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/16 14:40:48 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_command_error(char **argv)
{
	char	*full;
	int		cmd_len;
	int		exit_code;

	if (access(argv[0], F_OK))
		exit_code = 127;
	else
		exit_code = 126;
	cmd_len = ft_strlen(argv[0]);
	full = ft_calloc((cmd_len + 8), sizeof(char));
	if (!full)
		ft_exit_message("Failed to print error message");
	ft_strlcat(full, "pipex: ", (cmd_len + 8));
	ft_strlcat(full, argv[0], (cmd_len + 8));
	perror(full);
	ft_free_str_arr(argv);
	ft_free((void **)&full);
	exit(exit_code);
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
	int		fd;

	if (!command || !argv)
		return ;
	fd = open(command, O_DIRECTORY);
	if (fd == -1)
		return ;
	close(fd);
	ft_free_str_arr(argv);
	cmd_len = ft_strlen(command);
	full = ft_calloc(25 + cmd_len, sizeof(char));
	if (!full)
		ft_exit_message("Failed to print error message");
	ft_strlcat(full, "pipex: ", (cmd_len + 25));
	ft_strlcat(full, command, (cmd_len + 25));
	ft_strlcat(full, ": Is a directory\n", (cmd_len + 25));
	ft_putstr_fd(full, 2);
	ft_free((void **)&full);
	ft_free((void **)&command);
	exit(126);
}
