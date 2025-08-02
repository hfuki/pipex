#include "pipex.h"
#include "libft/libft.h"
#include <unistd.h>

void	child1(int inp_fd, int *pipefd, char *cmd, char **envp)
{
	char	*path;
	char	*cmd_args[4];

	if (dup2(inp_fd, STDIN_FILENO) < 0)
		error_exit_code("dup2 inp_fd failed", 1);
	if (dup2(pipefd[1], STDOUT_FILENO) < 0)
		error_exit_code("dup2 pipefd[1] failed", 1);
	close(pipefd[0]);
	cmd_args[0] = "sh";
	cmd_args[1] = "-c";
	cmd_args[2] = cmd;
	cmd_args[3] = NULL;
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
		error_exit_code("command not found", 127);
	execve(path, cmd_args, envp);
	free(path);
	error_exit_code("execve failed", 127);
}

void	child2(int out_fd, int *pipefd, char *cmd, char **envp)
{
	char	*cmd_args[4];
	char	*path;

	if (dup2(pipefd[0], STDIN_FILENO) < 0)
		error_exit_code("dup2 pipefd[0] failed", 1);
	if (dup2(out_fd, STDOUT_FILENO) < 0)
		error_exit_code("dup2 out_fd failed", 1);
	close(pipefd[1]);
	cmd_args[0] = "sh";
	cmd_args[1] = "-c";
	cmd_args[2] = cmd;
	cmd_args[3] = NULL;
	path = get_cmd_path(cmd_args[0], envp);
	if (!path)
		error_exit_code("command not found", 127);
	execve(path, cmd_args, envp);
	free(path);
	error_exit_code("execve failed", 127);
}
