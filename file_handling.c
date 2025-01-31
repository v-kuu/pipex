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

void	ft_open_files(char *infile, char *outfile, int files[2], bool heredoc)
{
	if (heredoc == true)
		files[0] = ft_read_heredoc(infile);
	else
		files[0] = ft_open(infile, READ);
	if (files[0] == -1)
		perror("Infile error");
	if (heredoc == true)
		files[1] = ft_open(outfile, APPEND);
	else
		files[1] = ft_open(outfile, TRUNC);
	if (files[1] == -1)
	{
		perror("Outfile error");
		if (files[0] != -1)
		close(files[0]);
	}
	if (files[1] == -1 || files[0] == -1)
		exit(EXIT_FAILURE);
}

static int	ft_open(char *file, int mode)
{
	if (mode == READ && access(file, R_OK | O_CLOEXEC) != -1)
		return (open(file, O_RDONLY));
	else if (mode == TRUNC && access(file, W_OK) != -1)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (mode == APPEND && access(file, W_OK) != -1)
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
		{
			perror("Heredoc failure");
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(STDOUT_FILENO, line, ft_strlen(line));
		free(line);
	}
}
