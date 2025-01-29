/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:03:00 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/29 12:10:41 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_glue_path(char *path, char *name)
{
	int		path_len;
	int		name_len;
	char	*full;

	path_len = ft_strlen(path);
	name_len = ft_strlen(name);
	full = ft_calloc((path_len + name_len + 2), sizeof(char));
	if (!full)
		return (NULL);
	ft_strlcat(full, path, path_len + 1);
	ft_strlcat(full, "/", 2);
	ft_strlcat(full, name, name_len + 1);
	return (full);
}
