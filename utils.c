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

static char *substr_spe(char *cmd, int spe1, int len, int second_com)
{
	int		spe2;
	char	*arr_spe_first;
	char	*arr_spe_bet;
	char	*arr_spe_last;
	char	*res_first;

	spe2 = spe1 + 2;
	while (cmd[spe2] && cmd[spe2] != '\\')
		spe2++;
	arr_spe_first = ft_substr(cmd, second_com, spe1 - second_com);
	arr_spe_bet = ft_substr(cmd, spe1 + 1, spe2 - (spe1 + 1));
	arr_spe_last = ft_substr(cmd, spe2 + 1, len - (spe2 + 1) - 1);
	if (!arr_spe_first || !arr_spe_bet || !arr_spe_last)
		return (NULL);
	res_first = ft_strjoin(arr_spe_first, arr_spe_bet);
	if (!res_first)
		return (NULL);
	return (ft_strjoin(res_first, arr_spe_last));
}

static char	*get_substr(char *cmd)
{
	int		i;
	int		j;
	int		len;

	i = 3;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '"' || cmd[i] == '\'')
		i++;
	len = ft_strlen(cmd);
	j = 0;
	while (cmd[j])
	{
		if (cmd[j] == '\\')
			return (substr_spe(cmd, j, len, i));
		j++;
	}
	return (ft_substr(cmd, i, len - i - 1));
}

char	**split_awk(char *cmd)
{
	char	**res;
	char	*arg;

	arg = get_substr(cmd);
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
