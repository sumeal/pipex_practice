/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:41:37 by muzz              #+#    #+#             */
/*   Updated: 2025/01/14 17:45:06 by muzz             ###   ########.fr       */
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

char	*check_path(char **split_path, char *cmd)
{
	int		i;
	char	*path;

	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *cmd)
{
	char	*path;
	char	**split_path;
	
	path = get_long_path(envp);
	split_path = ft_split(path, ':');
	path = check_path(split_path, cmd);
	return (path);
}

void	pipex(int fd1, int fd2, char **argv, char **envp)
{
	int		pfd[2];
	char	*path;
	char	**cmd1;
	char	**cmd2;
	pid_t	fork1;
	pid_t	fork2;
	
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');	
	if (pipe(pfd) == -1)
	{
		perror("Error pipe\n");
		exit(1);
	}
	if ((fork1 = fork()) == -1)
	{
		perror("Error fork\n");
		exit(1);
	}
	if (fork1 == 0)
	{
		path = get_path(envp, cmd1[0]);
		close(pfd[0]);
		dup2(fd1, 0);
		close(fd1);
		dup2(pfd[1], 1);
		close(pfd[1]);
		execve(path, cmd1, envp);
	}
	if ((fork2 = fork()) == -1)
	{
		perror("Error fork\n");
		exit(1);
	}
	if (fork2 == 0)
	{
		path = get_path(envp, cmd2[0]);
		close(pfd[1]);
		dup2(fd2, 1);
		close(fd2);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execve(path, cmd2, envp);
	}
	close(pfd[0]);
	close(pfd[1]);
	waitpid(fork1, NULL, 0);
	waitpid(fork2, NULL, 0);
	return ;
}
