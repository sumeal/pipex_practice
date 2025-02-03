/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:57:10 by abin-moh          #+#    #+#             */
/*   Updated: 2025/02/03 16:52:57 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *cmd)
{
	ft_printf("bash: %s: %s\n", cmd, strerror(errno));
	exit(0);
}

void	check_path(char **argv, char **envp)
{
	char	**cmd_split;
	char	*path;
	char	*cmd;

	cmd = ft_strdup(argv[2]);
	cmd_split = ft_split(cmd, ' ');
	path = get_path(envp, cmd_split[0], -1);
	if (!path)
	{
		ft_printf("%s: command not found\n", cmd_split[0]);
		cleanup_and_exit(cmd_split, path, 127);
	}
	cmd = ft_strdup(argv[3]);
	path = get_path(envp, cmd_split[0], -1);
	if (!path)
	{
		ft_printf("%s: command not found\n", cmd_split[0]);
		cleanup_and_exit(cmd_split, path, 127);
	}
	free_split(cmd_split);
	free(path);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		write(2, "Error\nInvalid number of arguments\n", 35);
		exit(1);
	}
	if (access(argv[1], F_OK) != 0)
		print_error(argv[1]);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
		print_error(argv[1]);
	fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
		print_error(argv[4]);
	check_path(argv, envp);
	pipex(fd1, fd2, argv, envp);
	close(fd1);
	close(fd2);
	return (0);
}
