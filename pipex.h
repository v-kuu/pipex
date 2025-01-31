/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:15:54 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/23 13:46:35 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

# define APPEND 0
# define READ 1
# define TRUNC 2

typedef struct s_cmd
{
	char	*path;
	char	**args;
}			t_cmd;

void	ft_open_files(char *infile, char *outfile, int files[2], bool heredoc);
t_cmd	*ft_parse_cmds(int count, char **args, char **envp, t_cmd *commands);

#endif
