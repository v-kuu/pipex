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

static int	ft_open_file(char *file, int mode);
static void	ft_create_cmd(t_cmd *cmd, char **paths, char **args, int index);
static char	*ft_test_path(char **paths, char *name);

int	*ft_check_files(int argc, char **argv)
{
	int	*files;

	files[0] = ft_open_file(argv[1], 0);
	if (files[0] < 0)
		return (NULL);
	files[1] = ft_open_file(argv[argc - 2], 1);
	if (files[1] < 0)
	{
		if (files[0] != 1)
			close(files[0]);
		return (NULL);
	}
	return (files);
}

static int	ft_open_file(char *file, int mode)
{
	if (mode == 0 && ft_strncmp(file, "<<", 2) == 0)
		return (1);
	else if (mode == 0 && access(file, R_OK) != -1)
		return (open(file, O_RDONLY));
	else if (mode == 1 && access(file, W_OK) != -1)
		return (open(file, O_WRONLY | O_CREAT, 0644));
	else
		return (-1);
}

t_cmd	*ft_parse_commands(int count, char **args, char **envp, t_cmd *commands)
{
	char	*path;
	char	**paths;
	int		index;

	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			path = &envp[index][5];
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (ft_free_commands(commands, count));
	index = -1;
	while (++index < count)
	{
		ft_create_cmd(&commands[index], paths, args, index);
		if (!commands[index].path)
			return (ft_free_commands(commands, count));
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
			break;
		ft_free((void **)&path);
		paths++;
	}
	return (path);
}
