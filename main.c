/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfuki <hfuki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:45:03 by hfuki             #+#    #+#             */
/*   Updated: 2025/08/20 14:45:03 by hfuki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <unistd.h>

int	main(int argc, char **argv, char **envp)
{
	int	inp_fd;
	int	out_fd;
	int	code;

	if (argc == 5)
	{
		inp_fd = open(argv[1], O_RDONLY);
		if (inp_fd < 0)
		{
			inp_fd = open("/dev/null", O_RDONLY);
			if (inp_fd < 0)
				error_exit_code("open infile failed", 0);
		}
		out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd < 0)
			error_exit_code("open outfile failed", 1);
		code = pipex(inp_fd, out_fd, argv, envp);
	}
	else
	{
		write(2, "Usage: ./pipex infile cmd1 cmd2 outfile\n", 41);
		return (1);
	}
	return (code);
}
