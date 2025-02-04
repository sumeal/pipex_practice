/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abin-moh <abin-moh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:19:30 by muzz              #+#    #+#             */
/*   Updated: 2025/02/04 12:29:32 by abin-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

void	pipex(int fd1, int fd2, char **argv, char **envp);
char	*get_path(char **envp, char *cmd);
void	free_split(char **split);
char	*get_path2(char **split_path, char *cmd);
//libft functions
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char const *s);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
//exec_child_helper.c
void	cleanup_and_exit(char **cmd_split, char *path, int exit_code);
void	handle_error_and_exit(
			char **cmd_split, char *path, const char *msg, int exit_code);
//pipiex_helper.c
void	handle_error(const char *msg);
char	**special_split(char *cmd);
#endif