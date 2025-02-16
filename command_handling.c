/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:03:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/16 14:40:39 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_glue_path(char *path, char *name);
static char	**ft_list_paths(char **envp);

char	*ft_test_paths(char *name, char **envp)
{
	char	*final;
	char	**paths;
	int		index;

	if (!name)
		return (NULL);
	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	paths = ft_list_paths(envp);
	if (!paths)
		return (NULL);
	index = -1;
	while (paths[++index])
	{
		final = ft_glue_path(paths[index], name);
		if (!final)
			return (ft_free_str_arr(paths));
		if (access(final, F_OK) == 0)
			break ;
		ft_free((void **)&final);
	}
	ft_free_str_arr(paths);
	return (final);
}

static char	**ft_list_paths(char **envp)
{
	int		index;
	char	**paths;

	if (!envp)
		return (NULL);
	index = -1;
	while (envp[++index])
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
			break ;
	if (!(envp[index]))
		return (NULL);
	paths = ft_split(&envp[index][5], ':');
	if (paths && !(*paths))
		return (ft_free((void **)&paths));
	return (paths);
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

void	ft_command_not_found(char *arg, char **envp)
{
	char	*argv[3];

	argv[0] = "/usr/lib/command-not-found";
	argv[1] = arg;
	argv[2] = NULL;
	execve(argv[0], argv, envp);
	perror("pipex:");
	exit(EXIT_FAILURE);
}

int	ft_find_path(char **envp)
{
	int	index;
	int	path_found;

	if (!envp)
		return (0);
	path_found = 0;
	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path_found = 1;
			break ;
		}
	}
	return (path_found);
}
