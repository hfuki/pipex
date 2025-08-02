#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pipex.h"

void	error_exit_code(const char *msg, int code)
{
	perror(msg);
	exit(code);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
