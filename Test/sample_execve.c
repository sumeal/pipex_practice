/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muzz <muzz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:43:18 by muzz              #+#    #+#             */
/*   Updated: 2025/01/14 10:45:59 by muzz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *const args[] = { "ls", NULL };
	char *const envp[] = { NULL };

	execve("/usr/bin/ls", args, envp);

	perror("execve");
	return (1);
}