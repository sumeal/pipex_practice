/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:36:18 by abin-moh          #+#    #+#             */
/*   Updated: 2025/02/04 10:43:33 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(const char *msg)
{
	perror(msg);
	exit(1);
}

char	**special_split(char *cmd)
{
	char	**cmd_split;

	cmd_split = NULL;
	if (cmd[0] == '"' && cmd[ft_strlen(cmd) - 1] == '"')
		cmd_split[0] = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
	return (cmd_split);
}
