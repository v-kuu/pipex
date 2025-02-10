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

static int	ft_read_heredoc(char *delim);
static void	ft_read_lines(char *delim);

int	ft_open_file(char *file, int mode)
{
	if (mode == 0)
		return (open(file, O_RDONLY));
	else if (mode == 1)
		return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else
		return (-1);
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
