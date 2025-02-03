/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:41:37 by muzz              #+#    #+#             */
/*   Updated: 2025/02/03 16:42:22 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_long_path(char **envp)
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

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path;
	char	**split_path;

	if (cmd[0] == '"' && cmd[ft_strlen(cmd) - 1] == '"')
		cmd = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_long_path(envp);
	split_path = ft_split(path, ':');
	if (!path || !split_path)
		return (NULL);
	if (get_path2(split_path, i))
	{
		free_split(split_path);
		return (path);
	}
	free_split(split_path);
	return (NULL);
}

char	*get_path2(char **split, int i)
{
	char	*path;
	char	*tmp;

	while (split[++i])
	{
		if (!split[i + 1])
			break ;
		tmp = ft_strjoin(split[i], "/");
		path = ft_strjoin(tmp, split[i + 1]);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

void	exec_child(int input_fd, int output_fd, char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	cmd_split = ft_split(cmd, ' ');
	path = get_path(envp, cmd_split[0], -1);
	if (!path)
	{
		ft_printf("%s: command not found\n", cmd_split[0]);
		cleanup_and_exit(cmd_split, path, 127);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1
		|| dup2(output_fd, STDOUT_FILENO) == -1)
		handle_error_and_exit(cmd_split, path, "dup2", 1);
	close(input_fd);
	close(output_fd);
	execve(path, cmd_split, envp);
	handle_error_and_exit(cmd_split, path, "execve", 1);
}

void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		pfd[2];
	pid_t	pids[2];

	if (pipe(pfd) == -1)
		handle_error("pipe");
	pids[0] = fork();
	if (pids[0] == 0)
	{
		close(pfd[0]);
		exec_child(infile, pfd[1], argv[2], envp);
	}
	waitpid(pids[0], NULL, 0);
	pids[1] = fork();
	if (pids[1] == 0)
	{
		close(pfd[1]);
		exec_child(pfd[0], outfile, argv[3], envp);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pids[1], NULL, 0);
}
