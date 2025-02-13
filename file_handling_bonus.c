/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:40 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_read_heredoc(char *delim, int pipe_fd[2]);
static void	ft_read_lines(char *delim);

int	ft_open_file(char *input, int mode, int pipe_fd[2])
{
	if (mode == HEREDOC)
		return (ft_read_heredoc(input, pipe_fd));
	else if (mode == READ)
		return (open(input, O_RDONLY));
	else if (mode == TRUNC)
		return (open(input, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (mode == APPEND)
		return (open(input, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (-1);
}

static int	ft_read_heredoc(char *delim, int pipe_fd[2])
{
	int		heredoc[2];
	pid_t	pid;

	if (pipe(heredoc) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(heredoc[0]);
		close(heredoc[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(heredoc[0]);
		dup2(heredoc[1], STDOUT_FILENO);
		close(heredoc[1]);
		ft_read_lines(delim);
	}
	close(heredoc[1]);
	wait(NULL);
	return (heredoc[0]);
}

static void	ft_read_lines(char *delim)
{
	char	*line;
	size_t	delim_len;

	delim_len = ft_strlen(delim);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(line, delim, delim_len) == 0
			&& line[delim_len + 1] == '\0')
		{
			ft_free((void **)&line);
			exit(EXIT_SUCCESS);
		}
		write(STDOUT_FILENO, line, ft_strlen(line));
		ft_free((void **)&line);
	}
}

void	ft_file_error(char *filename)
{
	char	*full;
	int		file_len;

	file_len = ft_strlen(filename);
	full = ft_calloc((file_len + 8), sizeof(char));
	if (!full)
	{
		perror("Failed to print error message");
		exit(EXIT_FAILURE);
	}
	ft_strlcat(full, "pipex: ", (file_len + 8));
	ft_strlcat(full, filename, (file_len + 8));
	perror(full);
	ft_free((void **)&full);
	exit(EXIT_FAILURE);
}
