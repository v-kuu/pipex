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

static char	*ft_glue_path(char *path, char *name);

char	*ft_test_paths(char *name, char **envp)
{
	char	*final;
	char	**paths;
	int		index;

	paths = NULL;
	index = -1;
	while (envp[++index])
	{
		if (ft_strncmp(envp[index], "PATH=", 5) == 0)
		{
			paths = ft_split(&envp[index][5], ':');
			break ;
		}
	}
	if (!paths)
		return (NULL);
	while (*paths)
	{
		final = ft_glue_path(*paths, name);
		if (access(final, X_OK) == 0)
			break ;
		ft_free((void **)&final);
		paths++;
	}
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
