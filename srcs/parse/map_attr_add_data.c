/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attr_add_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:43:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/16 19:28:54 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	read_map_2(t_data *data, t_map *map, enum e_map type)
{
	int		fd;
	char	*emap;

	fd = open(data->map_arg, O_RDONLY);
	while (1)
	{
		emap = get_next_line(fd);
		if (!emap)
		{
			free(emap);
			break ;
		}
		ms_lstadd_back(&map, ms_lstnew(type, ft_strdup(emap)));
		free(emap);
	}
	close(fd);
}

void	attr_add_data(char *line \
	, t_map **texture, enum e_map type, int *check)
{
	int	i;

	i = 0;
	*check += 1;
	if (type == SOUTH || type == NORTH || type == WEST || type == EAST)
	{
		i = 2;
		while (line[i] && line[i] == ' ')
			i++;
	}
	else if (type == FLOOR || type == CEILING)
	{
		i = 1;
		while (line[i] && line[i] == ' ')
			i++;
	}
	ms_lstadd_back(texture, ms_lstnew(type \
		, ft_substr(line + i, 0, ft_strlen(line + i))));
}

void	map_attr_add_data(t_data *data)
{
	t_map	*map;
	int		check;

	map = data->map_cub;
	check = 0;
	while (map)
	{
		if (map_find_attr(map->line, "SO"))
			attr_add_data(map->line, &(data->attr->texture), SOUTH, &check);
		else if (map_find_attr(map->line, "NO"))
			attr_add_data(map->line, &(data->attr->texture), NORTH, &check);
		else if (map_find_attr(map->line, "EA"))
			attr_add_data(map->line, &(data->attr->texture), EAST, &check);
		else if (map_find_attr(map->line, "WE"))
			attr_add_data(map->line, &(data->attr->texture), WEST, &check);
		else if (map_find_attr(map->line, "C"))
			attr_add_data(map->line, &(data->attr->color), CEILING, &check);
		else if (map_find_attr(map->line, "F"))
			attr_add_data(map->line, &(data->attr->color), FLOOR, &check);
		map = map->next;
		if (check == 6)
			break ;
	}
}