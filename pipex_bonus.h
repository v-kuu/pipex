/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:15:54 by vkuusela          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:33 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>

enum	e_mode
{
	READ,
	HEREDOC,
	TRUNC,
	APPEND
};

int		ft_open_file(char *input, int mode, int pipe_fd[2]);
void	ft_file_error(char *filename);
char	*ft_test_paths(char *name, char **envp);
void	ft_command_not_found(char *arg, char **envp);
int		ft_find_path(char **envp);
void	ft_first_cmd(char *arg, char **envp, char *infile, int heredoc);
void	ft_mid_cmd(char *arg, char **envp);
pid_t	ft_final_cmd(char *arg, char **envp, char *outfile, int heredoc);
void	ft_exit_message(char *message);
void	ft_exit_pipes(char *message, int fds[2]);
int		ft_command_error(char *command);
void	ft_is_command_directory(char *command, char **argv);

#endif
