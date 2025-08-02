#include "pipex.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int	pipex(int inp_fd, int out_fd, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	if (pipe(pipefd) == -1)
		error_exit_code("pipe failed", 1);
	pid1 = fork();
	if (pid1 == -1)
		error_exit_code("fork1 failed", 1);
	if (pid1 == 0)
		child1(inp_fd, pipefd, argv[2], envp);
	pid2 = fork();
	if (pid2 == -1)
		error_exit_code("fork2 failed", 1);
	if (pid2 == 0)
		child2(out_fd, pipefd, argv[3], envp);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	return (WEXITSTATUS(status2));
}
