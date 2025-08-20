/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfuki <hfuki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:45:16 by hfuki             #+#    #+#             */
/*   Updated: 2025/08/20 14:45:16 by hfuki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

void	child1(int inp_fd, int *pipefd, char *cmd, char **envp);
void	child2(int out_fd, int *pipefd, char *cmd, char **envp);
char	*get_cmd_path(char *cmd, char **envp);
int		pipex(int inp_fd, int out_fd, char **argv, char **envp);
void	error_exit_code(const char *msg, int code);
void	free_array(char **arr);
char	**split_awk(char *cmd);

#endif
