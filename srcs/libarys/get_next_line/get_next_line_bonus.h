/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:14:41 by ogenc             #+#    #+#             */
/*   Updated: 2023/11/12 22:39:54 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

size_t	gt_strlen(char *str);
char	*gt_strjoin(char *s1, char *s2);
int		ft_checknewline(char *buffer);
char	*ft_newline(char *buffer);
char	*new_buffer(char *buffer);
char	*read_line(int fd, char *buffer);
char	*get_next_line(int fd);
#endif
