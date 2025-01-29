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
