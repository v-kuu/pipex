/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:51:18 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/27 15:11:14 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scanner(char suspect, char const *set);

char	*ft_strtok(char *str, const char *delim)
{
	static char	*ptr;
	char		*token;
	int			index;

	if (str)
		ptr = str;
	if (!ptr)
		return (NULL);
	while (ft_scanner(*ptr, delim))
		ptr++;
	index = -1;
	while (ptr[++index])
	{
		if (ft_scanner(ptr[index], delim))
			break ;
	}
	token = ptr;
	token[index] = '\0';
	ptr += index;
	while (ft_scanner(ptr[index], delim))
		ptr++;
	return (token);
}

static int	ft_scanner(char suspect, char const *set)
{
	while (*set != 0)
	{
		if (suspect == *set)
			return (1);
		set++;
	}
	return (0);
}
