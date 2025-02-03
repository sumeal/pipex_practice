/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:00:32 by abin-moh          #+#    #+#             */
/*   Updated: 2025/02/03 16:38:25 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup_and_exit(char **cmd_split, char *path, int exit_code)
{
	if (cmd_split)
		free_split(cmd_split);
	if (path)
		free(path);
	exit(exit_code);
}

void	handle_error_and_exit(
	char **cmd_split, char *path, const char *msg, int exit_code)
{
	perror(msg);
	cleanup_and_exit(cmd_split, path, exit_code);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
