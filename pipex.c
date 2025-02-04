/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:41:37 by muzz              #+#    #+#             */
/*   Updated: 2025/02/04 16:33:30 by abin-moh         ###   ########.fr       */
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

char	*get_path(char **envp, char *cmd)
{
	char	*path;
	char	**split_path;
	char	*result;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_long_path(envp);
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	result = get_path2(split_path, cmd);
	free_split(split_path);
	return (result);
}

char	*get_path2(char **split_path, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	exec_child(int input_fd, int output_fd, char *cmd, char **envp)
{
	char	**cmd_split;
	char	*path;

	if (cmd[0] == '"' && cmd[ft_strlen(cmd) - 1] == '"')
		cmd = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
	if (cmd[1] == 't' && cmd[2] == 'r')
		cmd_split = special_split(cmd);
	else
		cmd_split = ft_split(cmd, ' ');
	path = get_path(envp, cmd_split[0]);
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
	if (execve(path, cmd_split, envp) == -1)
		ft_printf("this is error\n");
	handle_error_and_exit(cmd_split, path, "execve", 1);
}

void	pipex(int infile, int outfile, char **argv, char **envp)
{
	int		pfd[2];
	pid_t	pids[2];
	int		status1;
	int		status2;

	if (pipe(pfd) == -1)
		handle_error("pipe");
	pids[0] = fork();
	if (pids[0] == 0)
	{
		close(pfd[0]);
		exec_child(infile, pfd[1], argv[2], envp);
		handle_error("exec_child");
	}
	pids[1] = fork();
	if (pids[1] == 0)
	{
		close(pfd[1]);
		exec_child(pfd[0], outfile, argv[3], envp);
		handle_error("exec_child");
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pids[0], &status1, 0);
	waitpid(pids[1], &status2, 0);
	if (WIFEXITED(status2))
		exit(WEXITSTATUS(status2));
	else if (WIFEXITED(status1))
		exit(WEXITSTATUS(status1));
	else
		exit(1);
}
