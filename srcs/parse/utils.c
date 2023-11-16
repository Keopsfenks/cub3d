/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:18:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/16 19:32:06 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	read_map(t_data *data)
{
	int		fd;
	char	*map;

	fd = open(data->map_arg, O_RDONLY);
	while (1)
	{
		map = get_next_line(fd);
		if (!map)
		{
			free(map);
			break ;
		}
		ms_lstadd_back(&data->map_cub, ms_lstnew(MAP,ft_strdup(map)));
		free(map);
	}
	close(fd);
}