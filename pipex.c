/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuusela <vkuusela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 14:20:32 by vkuusela          #+#    #+#             */
/*   Updated: 2025/01/22 14:21:30 by vkuusela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **envp)
{
	int	index;
	int	files[2];

	if (argc < 5)
	{
		ft_printf("Usage: ./pipex <infile/here_doc> <cmd1>...<cmdn> outfile>");
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		index = 3;
		ft_open_files(argv[2], argv[argc - 1], files, true);
	}
	else
	{
		index = 2;
		ft_open_files(argv[1], argv[argc - 1], files, false);
		dup2(files[0], STDIN_FILENO);
	}
	while (index < argc - 2)
		ft_pass_to_child(argv[index++], envp);
	dup2(files[1], STDOUT_FILENO);
	ft_exec(argv[argc - 2], envp);
}
