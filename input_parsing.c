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

static int		ft_open_file(char *file, int mode);
static t_cmd	ft_test_path(char **path_arr, char **args, int index);

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
	char	*pwd;
	char	*path;
	char	**path_arr;
	int		index;

	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PWD=", 4) == 0)
			pwd = &envp[index][4];
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			path = &envp[index][5];
	}
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (NULL);
	index = -1;
	while (++index < count)
	{
		commands[index] = ft_test_path(path_arr, args, index);
	}
	ft_free_str_arr(path_arr);
	return (commands);
}

static t_cmd	ft_test_path(char **path_arr, char **args, int index)
{

}
