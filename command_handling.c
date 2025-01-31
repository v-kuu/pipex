/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:03:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/31 16:08:12 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_create_cmd(t_cmd *cmd, char **paths, char **args, int index);
static char	*ft_test_path(char **paths, char *name);
static char	*ft_glue_path(char *path, char *name);

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

static char	*ft_glue_path(char *path, char *name)
{
	int		path_len;
	int		name_len;
	int		full_len;
	char	*full;

	path_len = ft_strlen(path);
	name_len = ft_strlen(name);
	full_len = path_len + name_len + 2;
	full = ft_calloc(full_len, sizeof(char));
	if (!full)
		return (NULL);
	ft_strlcat(full, path, full_len);
	ft_strlcat(full, "/", full_len);
	ft_strlcat(full, name, full_len);
	return (full);
}
