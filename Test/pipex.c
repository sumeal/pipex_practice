/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:03:35 by muzz              #+#    #+#             */
/*   Updated: 2025/01/14 10:24:19 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(void)
{
	int arr[] = { 1, 2, 3, 4, 1, 2 };
	int arrSize = sizeof(arr) / sizeof(int);
	int start, end;
	int fd[2];
	if (pipe(fd) == -1)
	{
		return (1);
	}
	int id = fork();
	if (id == -1)
	{
		return (2);
	}
	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		waitpid(id, NULL, 0);
		start = arrSize / 2;
		end = arrSize;
	}
	int sum = 0;
	int i;
	for (i = start ; i < end; i++)
	{
		sum +=arr[i];
	}
	printf("Cal cualted partial sum %d\n", sum);
}