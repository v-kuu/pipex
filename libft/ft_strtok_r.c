/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 11:21:34 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/06 11:31:47 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_scanner(char suspect, char const *set);

char	*ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char		*token;
	int			index;

	if (str)
		*saveptr = str;
	if (!*saveptr)
		return (NULL);
	while (ft_scanner(**saveptr, delim))
		(*saveptr)++;
	index = -1;
	while (*saveptr[++index])
	{
		if (ft_scanner((*saveptr)[index], delim))
			break ;
	}
	token = *saveptr;
	token[index] = '\0';
	*saveptr += index;
	while (ft_scanner(**saveptr, delim))
		(*saveptr)++;
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
