#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pipex.h"
#include "libft/libft.h"

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

char	**split_awk(char *cmd)
{
	char	**res;
	char	*arg;
	int		i;
	int		len;

	i = 3;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '"' || cmd[i] == '\'')
		i++;
	len = ft_strlen(cmd);
	arg = ft_substr(cmd, i, len - i - 1);
	if (!arg)
		return (NULL);
	res = malloc(sizeof(char *) * 3);
	if (!res)
	{
		free(arg);
		return (NULL);
	}
	res[0] = ft_strdup("awk");
	res[1] = arg;
	res[2] = NULL;
	return (res);
}
