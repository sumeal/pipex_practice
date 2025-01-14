/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:02:35 by muzz              #+#    #+#             */
/*   Updated: 2025/01/14 17:28:50 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
	{
		write(2, "Error: Invalid number of arguments\n", 35);
		return (1);
	}
	fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd1 < 0 || fd2 < 0)
	{
		perror ("Error");
		return (1);
	}
	pipex(fd1, fd2, argv, envp);
	return (0);
}
