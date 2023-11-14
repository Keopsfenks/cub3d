/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:10:10 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/14 09:44:28 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		ms_lstadd_back(&data->map, ms_lstnew(ft_strdup(map)));
		free(map);
	}
}

bool	map_find_attr(char *line, char *find)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(find);
	while (line[++i] != '\0')
	{
		if (size == 2)
			if (line[i] == find[0] \
				&& line[i + 1] == find[1])
				return (true);
		if (size == 1)
			if (line[i] == find[0])
				return (true);
	}
	return (false);
}

void	parse_with_map_content(char *line, bool *flag, int *check)
{
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		*check += 1;
		return ;
	}
	else if (ft_strncmp(line, "NO", 2) == 0)
	{
		*check += 1;
		return ;
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		*check += 1;
		return ;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		*check += 1;
		return ;
	}
	*flag = true;
}

void	parse_with_color(char *line, bool *flag, int *rule)
{
	int	comma;
	int	i;
	int	check;

	comma = 2;
	check = 0;
	i = -1;
	if (ft_strncmp(line, "F", 1) == 0)
	{
		check = 1;
		*rule += 1;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		check = 1;
		*rule += 1;
	}
	if (check == 0)
		*flag = true;
	while (line[++i] != '\0')
		if (ft_isdigit(line[i]))
			break ;
	while (line[i])
	{
		while (comma == 0 && line[i] == ' ')
			i++;
		if (!(ft_isdigit(line[i]) || line[i] == ' ' \
			|| line[i] == ',') && comma != 0)
			*flag = true;
		if (comma == 0 && !(ft_isdigit(line[i]) || line[i] == '\n'))
			*flag = true;
		if (line[i] == ',')
			comma--;
		i++;
	}
}

void	map_invalid_char(char *line, bool **flag)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' \
			&& line[i] != '0' && line[i] != '2' \
			&& line[i] != 'N' && line[i] != 'S' \
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			**flag = true;
	}
}

bool	map_surarround_wall_check2(t_map *map, int i)
{
	int	wall_end;
	int	j;

	j = i;
	while (map->line[j] && map->line[j] == ' ')
		j++;
	while (map && map->line[i] == ' ')
	{
		if (map->line[j] != '1' || map->line[i - 1] != '1')
			return (true);
		map = map->next;
	}
	wall_end = j;
	i -= 1;
	while (map->line[i] != '\0' && i != wall_end)
	{
		if (map->line[i] != '1')
			return (true);
		i++;
	}
	return (false);
}

bool	map_surarround_wall_check3(t_map *map, int i)
{
	int	wall_end;
	int	j;

	j = i;
	while (map->line[j] && map->line[j] == ' ')
		j++;
	while (map && map->line[i] == ' ')
	{
		if (map->line[j] != '1' || map->line[i - 1] != '1')
			return (true);
		map = map->prev;
	}
	wall_end = j;
	i -= 1;
	while (map->line[i] != '\0' && i != wall_end)
	{
		if (map->line[i] != '1')
			return (true);
		i++;
	}
	return (false);
}

void	map_surarround_wall_check(t_map *map, bool **flag)
{
	int			i;
	static bool	flag2 = true;
	t_map		*last;

	i = -1;
	last = ms_lstlast(map);
	if ((map->prev->line[0] == '\0' || map->prev->line[0] == '\n') \
		&& ft_strlen(map->prev->line) <= 1 && flag2)
	{
		while (map->line[++i] != '\n' && map->line[i] != '\0')
		{
			if (map->line[i] != '1' && map->line[i] != ' ')
				**flag = true;
			else if (map->line[i] == ' ' \
				&& map->line[i + 1] == '1'
				&& map->line[i - 1] == '1')
				if (map_surarround_wall_check2(map, i))
					**flag = true;
		}
	}
	i = 0;
	while (map->line[i] && map->line[i] == ' ')
		i++;
	if (map->line[i] != '1' && map->line[ft_strlen(map->line) - 1] != '1')
		**flag = true;
	i = -1;
	while (last->line[++i] != '\n' && last->line[i] != '\0' && flag2)
	{
		if (last->line[i] != '1' && last->line[i] != ' ')
			**flag = true;
		else if (last->line[i] == ' ' \
			&& last->line[i + 1] == '1'
			&& last->line[i - 1] == '1')
			if (map_surarround_wall_check3(last, i))
				**flag = true;
	}
	flag2 = false;
}

void	which_select_parse2(t_map *map, bool *flag)
{
	bool	check;

	check = true;
	while (map && *flag == false)
	{
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1 && check)
		{
			map = map->next;
			continue ;
		}
		check = false;
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1)
			*flag = true;
		map_invalid_char(map->line, &flag);
		map_surarround_wall_check(map, &flag);
		map = map->next;
	}
}

bool	where_attr_map(t_map *map, bool *flag)
{
	if (!map)
		return (*flag = true, true);
	if (map && map->line[0] == '\0')
		return (*flag = true, true);
	return (true);
}

bool	which_select_parse(t_data *data)
{
	bool	flag;
	int		check;

	flag = false;
	check = 0;
	while (data->map)
	{
		if (map_find_attr(data->map->line, "SO")
			|| map_find_attr(data->map->line, "NO")
			|| map_find_attr(data->map->line, "WE")
			|| map_find_attr(data->map->line, "EA"))
			parse_with_map_content(data->map->line, &flag, &check);
		if (map_find_attr(data->map->line, "F") \
			|| map_find_attr(data->map->line, "C"))
			parse_with_color(data->map->line, &flag, &check);
		data->map = data->map->next;
		if (check == 6)
			if (where_attr_map(data->map, &flag))
				break ;
	}
	if (flag == false)
		which_select_parse2(data->map, &flag);
	return (flag);
}

void	ft_parse(t_data *data)
{
	read_map(data);
	if (which_select_parse(data))
		ft_error();
	map_attr_add_data(data);
}
