/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_attr_add_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:43:31 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/17 04:17:26 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	attr_add_data2(enum e_map type, char *line, int *i)
{
	char	*str;
	int		fd;

	if (type == SOUTH || type == NORTH || type == WEST || type == EAST)
	{
		(*i) = 2;
		while (line[(*i)] && line[(*i)] == ' ')
			(*i)++;
		str = ft_substr(line, (*i), ft_strlen(line + (*i)) - 1);
		fd = open(str, O_RDONLY);
		free(str);
		if (fd < 0)
			ft_error();
		close(fd);
	}
}

void	attr_add_data(char *line \
	, t_map **texture, enum e_map type, int *check)
{
	int		i;

	i = 0;
	*check += 1;
	attr_add_data2(type, line, &i);
	if (type == FLOOR || type == CEILING)
	{
		i = 1;
		while (line[i] && line[i] == ' ')
			i++;
	}
	ms_lstadd_back(texture, ms_lstnew(type \
		, ft_substr(line, i, ft_strlen(line + i) - 1)));
}

void	num_limit_check2(t_map *tmp, int *i, int *size, int *num)
{
	char	*str;

	if (tmp->line[(*i)] == ',' || tmp->line[(*i)] == '\n')
	{
		str = ft_substr(tmp->line, (*num) - (*size), (*size));
		if (ft_atoi(str) > 255)
			ft_error();
		(*size) = 0;
		free(str);
	}
}

void	num_limit_check(t_map *color)
{
	t_map	*tmp;
	int		i;
	int		size;
	int		num;

	tmp = color;
	size = 0;
	num = 0;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
		{
			if (ft_isdigit(tmp->line[i]))
			{
				size++;
				num = i + 1;
			}
			num_limit_check2(tmp, &i, &size, &num);
		}
		tmp = tmp->next;
	}
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
	num_limit_check(data->attr->color);
}
