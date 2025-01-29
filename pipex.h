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

typedef struct s_cmd
{
	char	*path;
	char	**args;
}			t_cmd;

void	ft_check_files(int argc, char **argv, int files[2]);
t_cmd	*ft_parse_cmds(int count, char **args, char **envp, t_cmd *commands);
void	*ft_free_commands(t_cmd *commands, int size);
char	*ft_glue_path(char *path, char *name);
void	ft_exit(const char *string, t_cmd *commands, int size);

#endif
