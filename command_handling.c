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

char	*ft_test_paths(char *name, char *path)
{
	char	*final;
	char	**path_arr;
	int		index;

	if (!name)
		return (NULL);
	if (ft_strchr(name, '/'))
		return (ft_strdup(name));
	path_arr = ft_split(path, ':');
	if (!path_arr)
		return (NULL);
	index = -1;
	while (path_arr[++index])
	{
		final = ft_glue_path(path_arr[index], name);
		if (!final)
			return (ft_free_str_arr(path_arr));
		if (access(final, F_OK) == 0)
			break ;
		ft_free((void **)&final);
	}
	ft_free_str_arr(path_arr);
	return (final);
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

void	ft_command_not_found(char *arg, char **command, char **envp)
{
	char	*argv[3];

	argv[0] = "/usr/lib/command-not-found";
	argv[1] = arg;
	argv[2] = NULL;
	execve(argv[0], argv, envp);
	perror("pipex:");
	ft_free_str_arr(command);
	exit(EXIT_FAILURE);
}

char	*ft_find_path(char **envp)
{
	int		index;
	char	*path;

	if (!envp)
		return (NULL);
	path = NULL;
	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			path = &envp[index][5];
			break ;
		}
	}
	return (path);
}
