/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:15:54 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/06 14:30:48 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

int		ft_open_file(char *file, int mode);
char	*ft_test_paths(char *name, char **envp);
void	ft_first_cmd(char *arg, char **envp, char *infile);
pid_t	ft_final_cmd(char *arg, char **envp, char *outfile);
void	ft_command_not_found(char *arg, char **envp);
void	ft_file_error(char *filename);
int		ft_command_error(char *command);
void	ft_exit_message(char *message);
void	ft_exit_pipes(char *message, int fds[2]);

#endif
