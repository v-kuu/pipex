/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/31 16:01:19 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *file, int mode);
static int	ft_read_heredoc(char *delim);
static void	ft_read_lines(char *delim);

int	ft_open_file(char *input, int mode)
{
	int	file;

	if (mode == HEREDOC)
		file = ft_read_heredoc(input);
	else if (mode == READ)
		file = ft_open(input, READ);
	else if (mode == TRUNC)
		file = ft_open(input, TRUNC);
	else if (mode == APPEND)
		file = ft_open(input, APPEND);
	else
		return (-1);
	return (file);
}

static int	ft_open(char *file, int mode)
{
	if (mode == READ)
		return (open(file, O_RDONLY));
	else if (mode == TRUNC)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (mode == APPEND)
		return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	else
		return (-1);
}

static int	ft_read_heredoc(char *delim)
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

	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			exit(EXIT_SUCCESS);
		if (ft_strlen(delim) == ft_strlen(line)
			&& (ft_strncmp(line, delim, ft_strlen(delim)) == 0))
		{
			free(line);
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
