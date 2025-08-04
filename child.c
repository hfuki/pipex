#include "pipex.h"
#include "libft/libft.h"
#include <unistd.h>

void	child1(int inp_fd, int *pipefd, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(inp_fd, STDIN_FILENO) < 0)
		error_exit_code("dup2 inp_fd failed", 1);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_exit_code("dup2 pipefd[1] failed", 1);
	close(pipefd[0]);
	if (ft_strncmp(cmd, "awk ", 4) == 0)
		cmd_args = split_awk(cmd);
	else
		cmd_args = ft_split(cmd, ' ');
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
	{
		free_array(cmd_args);
		error_exit_code("command not found", 127);
	}
	execve(path, cmd_args, envp);
	free(path);
	free_array(cmd_args);
	error_exit_code("execve failed", 127);
}

void	child2(int out_fd, int *pipefd, char *cmd, char **envp)
{
	char	**cmd_args;
	char	*path;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error_exit_code("dup2 pipefd[0] failed", 1);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		error_exit_code("dup2 out_fd failed", 1);
	close(pipefd[1]);
	if (ft_strncmp(cmd, "awk ", 4) == 0)
		cmd_args = split_awk(cmd);
	else
		cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		error_exit_code("split failed", 1);
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
	{
		free_array(cmd_args);
		error_exit_code("command not found", 127);
	}
	execve(path, cmd_args, envp);
	free_array(cmd_args);
	free(path);
	error_exit_code("execve failed", 127);
}
