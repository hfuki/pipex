#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "pipex.h"
#include "libft/libft.h"

static char	*find_path_env(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*join_path_cmd(char *dir, char *cmd)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, cmd);
	if (!res)
		return (free(tmp), NULL);
	free(tmp);
	return (res);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*f_path;
	char	*full;
	char	**paths;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	f_path = find_path_env(envp);
	if (!f_path)
		return (NULL);
	paths = ft_split(f_path, ':');
	i = 0;
	while (paths[i])
	{
		full = join_path_cmd(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_array(paths), full);
		free(full);
		i++;
	}
	return (free_array(paths), NULL);
}
