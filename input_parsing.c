/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:01:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/23 13:47:13 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_open(char *file, int mode);
static int	ft_read_heredoc(char *delim);
static void	ft_read_lines(char *delim);
static void	ft_create_cmd(t_cmd *cmd, char **paths, char **args, int index);
static char	*ft_test_path(char **paths, char *name);

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
		line = get_next_line(1);
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
		write(1, line, ft_strlen(line));
		free(line);
	}
}

t_cmd	*ft_parse_cmds(int count, char **args, char **envp, t_cmd *commands)
{
	char	*path;
	char	**paths;
	int		index;

	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path = &envp[index][5];
			break ;
		}
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (ft_free_commands(commands));
	index = -1;
	while (++index < count)
	{
		ft_create_cmd(&commands[index], paths, args, index);
		if (!commands[index].path)
			return (ft_free_commands(commands));
	}
	ft_free_str_arr(paths);
	return (commands);
}

static void	ft_create_cmd(t_cmd *cmd, char **paths, char **args, int index)
{
	cmd->args = ft_split(args[index], ' ');
	if (!cmd->args)
		return ;
	cmd->path = ft_test_path(paths, cmd->args[0]);
}

static char	*ft_test_path(char **paths, char *name)
{
	char	*path;

	while (*paths)
	{
		path = ft_glue_path(*paths, name);
		if (access(path, X_OK) == 0)
			break ;
		ft_free((void **)&path);
		paths++;
	}
	return (path);
}
