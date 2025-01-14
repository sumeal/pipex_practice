/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parent_from_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:16:51 by muzz              #+#    #+#             */
/*   Updated: 2025/01/14 14:28:45 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("Pipe error\n");
		return (1);
	}
	if ((pid = fork()) == -1)
	{
		perror("Fork error\n");
		return (2);
	}
	if (pid == 0)
	{
		close(pfd[0]);
		write(pfd[1], "Hello", 5);
		close(pfd[1]);
			exit(EXIT_SUCCESS);
	}
	else
	{
		char str[20];

		close(pfd[1]);
		read(pfd[0], str, 3);
		close(pfd[0]);
		str[3] = '\0';
		printf("str = %s\n", str);
		close(pfd[0]);
		wait(NULL);
	}
	return (EXIT_SUCCESS);
}